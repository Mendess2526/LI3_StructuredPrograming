#include "calendario.h"
#include "dateTime.h"
#include "post.h"
#include <string.h>

#define ANO2INDEX(ano) (ano-2008)

typedef GSList * POSTS;

typedef struct _hora{
    int count;
    POSTS posts;
} *HORA;

typedef struct _dia{
    HORA *horas;
} *DIA;

typedef struct _mes{
    int nDias;
    DIA *dias;
} *MES;

typedef struct _ano{
    MES *meses;
} *ANO;

struct _calendario{
    int nAnos;
    ANO *anos;
    CCompareFunc compareFunc;
    CFreeFunc freeFunc;
};

static int nrDias (int m);
gint timeCompare(gconstpointer a, gconstpointer b);

static HORA hora_create();
static DIA dia_create();
static MES mes_create(int nDias);
static ANO ano_create();

static inline void hora_add_post(HORA h, void* p, CCompareFunc compareFunc);
static void dia_add_post(DIA dia, DATETIME d, void* post, CCompareFunc compareFunc);
static void mes_add_post(MES mes, DATETIME d, void* post, CCompareFunc compareFunc);
static void ano_add_post(ANO ano, DATETIME d, void* post, CCompareFunc compareFunc);

static inline void hora_get_post_ids(HORA hora, void *user_data, GFunc calFunc);
static inline void dia_get_post_ids(DIA dia, void *user_data, GFunc calFunc);
static inline void mes_get_post_ids(MES mes, Date from, Date to, int sameMonth, void* user_data, GFunc calFunc);
static inline void ano_get_post_ids(ANO ano, Date from, Date to, int sameYear, void* user_data, GFunc calFunc);

static void hora_destroy(HORA h, CFreeFunc freeFunc);
static void dia_destroy(DIA d, CFreeFunc freeFunc);
static void mes_destroy(MES m, CFreeFunc freeFunc);
static void ano_destroy(ANO a, CFreeFunc freeFunc);

static int nrDias (int m){
    if(m == 3 || m == 5 || m == 8 || m == 10) return 30;
    if(m == 1) return 29;
    return 31;
}


static HORA hora_create(){
    HORA h = (HORA) malloc(sizeof(struct _hora));
    h->count = 0;
    h->posts = NULL;
    return h;
}

static DIA dia_create(){
    DIA d = (DIA) malloc(sizeof(struct _dia));
    d->horas = (HORA *) calloc(24, sizeof(struct _hora *));
    return d;
}

static MES mes_create(int nDias){
    MES m = (MES) malloc(sizeof(struct _mes));
    m->nDias = nDias;
    m->dias = (DIA *) calloc(nDias, sizeof(struct _dia *));
    return m;
}

static ANO ano_create(){
    ANO a = (ANO) malloc(sizeof(struct _ano));
    a->meses = (MES *) calloc(12, sizeof(struct _mes *));
    return a;
}

CALENDARIO calendario_create(int nAnos, CCompareFunc compareFunc, CFreeFunc freeFunc){
    CALENDARIO c = (CALENDARIO) malloc(sizeof(struct _calendario));
    c->nAnos = nAnos;
    c->anos = (ANO *) calloc(nAnos, sizeof(struct _ano *));
    c->compareFunc = compareFunc;
    c->freeFunc = freeFunc;
    return c;
}

static inline void hora_add_post(HORA h, void* post, CCompareFunc compareFunc){
    h->count += 1;
    h->posts = g_slist_insert_sorted(h->posts, post, compareFunc);
}

static void dia_add_post(DIA dia, DATETIME d, void* post, CCompareFunc compareFunc){
    int hora = dateTime_get_horas(d);
    if(dia->horas[hora] == NULL) dia->horas[hora] = hora_create();
    hora_add_post(dia->horas[hora], post, compareFunc);
}

static void mes_add_post(MES mes, DATETIME d, void* post, CCompareFunc compareFunc){
    int dia = dateTime_get_dia(d);
    if(mes->dias[dia] == NULL) mes->dias[dia] = dia_create();
    dia_add_post(mes->dias[dia], d, post, compareFunc);
}

static void ano_add_post(ANO ano, DATETIME d, void* post, CCompareFunc compareFunc){
    int mes = dateTime_get_mes(d);
    if(ano->meses[mes] == NULL)
        ano->meses[mes] = mes_create(nrDias(mes));
    mes_add_post(ano->meses[mes], d, post, compareFunc);
}

void calendario_add_post(CALENDARIO cal, void* post, DATETIME d){
    int ano = ANO2INDEX(dateTime_get_ano(d));
    if(cal->anos[ano] == NULL) cal->anos[ano] = ano_create();
    ano_add_post(cal->anos[ano], d, post, cal->compareFunc);
}

static inline void hora_get_post_ids(HORA hora, void *user_data, GFunc calFunc){
    if(!hora) return;
    printf("Count: %d\n", g_slist_length(hora->posts));
    g_slist_foreach(hora->posts, calFunc, user_data);
}

static inline void dia_get_post_ids(DIA dia, void *user_data, GFunc calFunc){
    if(!dia) return;
    for(int i=0; i<24; i++)
        hora_get_post_ids(dia->horas[i], user_data, calFunc);
}

static inline void mes_get_post_ids(MES mes, Date from, Date to, int sameMonth, void *user_data, GFunc calFunc){
    if(!mes) return;
    int fromD = get_day(from);
    int toD = sameMonth ? get_day(to) : mes->nDias;
    while(fromD < toD)
        dia_get_post_ids(mes->dias[fromD++], user_data, calFunc);
}

static inline void ano_get_post_ids(ANO ano, Date from, Date to, int sameYear, void *user_data, GFunc calFunc){
    if(!ano) return;
    int fromM = get_month(from);
    int toM = sameYear ? get_month(to) : 11;
    int sameMonth = sameYear && fromM == toM;
    while(fromM <= toM)
        mes_get_post_ids(ano->meses[fromM++], from, to, sameMonth, user_data, calFunc);
}

void calendario_get_ids(CALENDARIO cal, Date from, Date to, void *user_data, GFunc calFunc){
    int fromY = ANO2INDEX(get_year(from));
    int toY = ANO2INDEX(get_year(to));
    int sameYear = fromY == toY;
    while(fromY <= toY)
        ano_get_post_ids(cal->anos[fromY++], from, to, sameYear, user_data, calFunc);
}

static void hora_destroy(HORA h, CFreeFunc freeFunc){
    if(h==NULL) return;
    if(freeFunc) g_slist_free_full(h->posts, freeFunc);
    else g_slist_free(h->posts);
    free(h);
}

static void dia_destroy(DIA d, CFreeFunc freeFunc){
    if(d==NULL) return;
    for(int i=0; i<24; i++){
        hora_destroy(d->horas[i], freeFunc);
    }
    free(d->horas);
    free(d);
}

static void mes_destroy(MES m, CFreeFunc freeFunc){
    if(m==NULL) return;
    for(int i=0; i<(m->nDias); i++){
        dia_destroy(m->dias[i], freeFunc);
    }
    free(m->dias);
    free(m);
}

static void ano_destroy(ANO a, CFreeFunc freeFunc){
    if(a==NULL) return;
    for(int i=0; i<12; i++){
        mes_destroy(a->meses[i], freeFunc);
    }
    free(a->meses);
    free(a);
}

void calendario_destroy(CALENDARIO cal){
    for(int i=0; i<(cal->nAnos); i++){
        ano_destroy(cal->anos[i], cal->freeFunc);
    }
    free(cal->anos);
    free(cal);
}

static void printHora(HORA hora, CPrintFunction printFuncion){
    if(!hora) return;
    for(GSList *cur = hora->posts; cur; cur = g_slist_next(cur)){
        (*printFuncion)(cur->data);
    }
}

static void printDia(DIA dia, CPrintFunction printFuncion){
    if(!dia) return;
    for(int i=0; i<24; i++){
        printf("\t\t\tHora: %d\n",i);
        printHora(dia->horas[i], printFuncion);
    }
}

static void printMes(MES mes, CPrintFunction printFuncion){
    if(!mes) return;
    for(int i=0; i<mes->nDias; i++){
        printf("\t\tDia: %d\n",i);
        printDia(mes->dias[i], printFuncion);
    }
}

static void printAno(ANO ano, CPrintFunction printFuncion){
    if(!ano) return;
    for(int i=0; i<12;i++){
        printf("\tMes: %d\n",i);
        printMes(ano->meses[i], printFuncion);
    }
}

void printCalendario(CALENDARIO cal, CPrintFunction printFuncion){
    for(int i=0; i< cal->nAnos; i++){
        printf("Ano: %d\n",i);
        printAno(cal->anos[i], printFuncion);
    }
}
