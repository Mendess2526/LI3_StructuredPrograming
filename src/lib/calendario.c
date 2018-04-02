#include "calendario.h"
#include "dateTime.h"
#include "post.h"
#include <string.h>

/** Macro para compara dois inteiros positivos */
#define INT_CMP(a,b) ((a > b) - (a < b))
#define ANO2INDEX(ano) (ano-2008)

typedef GSList * POSTS;

typedef struct _hora{
    int count;
    POSTS posts;
    CCompareFunc compareFunc;
} *HORA;

typedef struct _dia{
    HORA *horas;
    CCompareFunc compareFunc;
} *DIA;

typedef struct _mes{
    int nDias;
    DIA *dias;
    CCompareFunc compareFunc;
} *MES;

typedef struct _ano{
    MES *meses;
    CCompareFunc compareFunc;
} *ANO;

struct _calendario{
    int nAnos;
    ANO *anos;
    CCompareFunc compareFunc;
    CFreeFunc freeFunc;
};

static HORA hora_create(CCompareFunc compareFunc);
static inline void hora_add_post(HORA h, void* p);
static DIA dia_create();
static MES mes_create(int nDias);
static ANO ano_create();
static void dia_add_post(DIA dia, DATETIME d, void* post);
static void mes_add_post(MES mes, DATETIME d, void* post);
static void ano_add_post(ANO ano, DATETIME d, void* post);
static inline void hora_get_post_ids(HORA hora, void *user_data, GFunc calFunc);
static inline void dia_get_post_ids(DIA dia, void *user_data, GFunc calFunc);
static inline void mes_get_post_ids(MES mes, Date from, Date to, int sameMonth, void* user_data, GFunc calFunc);
static inline void ano_get_post_ids(ANO ano, Date from, Date to, int sameYear, void* user_data, GFunc calFunc);
static void dia_destroy(DIA d);
static void mes_destroy(MES m);
static void ano_destroy(ANO a);
static int nrDias (int m);

//TODO make generic struct
gint timeCompare(gconstpointer a, gconstpointer b){
    DATETIME dataA = post_get_date((POST) b);
    DATETIME dataB = post_get_date((POST) a);
    int c;
    c = INT_CMP(dateTime_get_horas(dataA),         dateTime_get_horas(dataB));
    if(c) return c;
    c = INT_CMP(dateTime_get_minutos(dataA),       dateTime_get_minutos(dataB));
    if(c) return c;
    c = INT_CMP(dateTime_get_segundos(dataA),      dateTime_get_segundos(dataB));
    if(c) return c;
    c = INT_CMP(dateTime_get_milissegundos(dataA), dateTime_get_milissegundos(dataB));
    if(c) return c;
    return 0;
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

static inline void hora_add_post(HORA h, void* p){
    h->count += 1;
    h->posts = g_slist_insert_sorted(h->posts, p, timeCompare);
}

static void dia_add_post(DIA dia, DATETIME d, void* post){
    int hora = dateTime_get_horas(d);
    if(dia->horas[hora] == NULL) dia->horas[hora] = hora_create();
    hora_add_post(dia->horas[hora], post);
}

static void mes_add_post(MES mes, DATETIME d, void* post){
    int dia = dateTime_get_dia(d);
    if(mes->dias[dia] == NULL) mes->dias[dia] = dia_create();
    dia_add_post(mes->dias[dia], d, post);
}

static int nrDias (int m){
    if(m == 3 || m == 5 || m == 8 || m == 10) return 30;
    if(m == 1) return 29;
    return 31;
}

static void ano_add_post(ANO ano, DATETIME d, void* post){
    int mes = dateTime_get_mes(d);
    if(ano->meses[mes] == NULL)
        ano->meses[mes] = mes_create(nrDias(mes));
    mes_add_post(ano->meses[mes], d, post);
}

void calendario_add_post(CALENDARIO cal, void* post, DATETIME d){
    int ano = ANO2INDEX(dateTime_get_ano(d));
    if(cal->anos[ano] == NULL) cal->anos[ano] = ano_create();
    ano_add_post(cal->anos[ano], d, post);
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

static void hora_destroy(HORA h){
    if(h==NULL) return;
    g_slist_free_full(h->posts, post_destroy_generic);
    free(h);
}

static void dia_destroy(DIA d){
    if(d==NULL) return;
    for(int i=0; i<24; i++){
        hora_destroy(d->horas[i]);
    }
    free(d->horas);
    free(d);
}

static void mes_destroy(MES m){
    if(m==NULL) return;
    for(int i=0; i<(m->nDias); i++){
        dia_destroy(m->dias[i]);
    }
    free(m->dias);
    free(m);
}

static void ano_destroy(ANO a){
    if(a==NULL) return;
    for(int i=0; i<12; i++){
        mes_destroy(a->meses[i]);
    }
    free(a->meses);
    free(a);
}

void calendario_destroy(CALENDARIO cal){
    for(int i=0; i<(cal->nAnos); i++){
        ano_destroy(cal->anos[i]);
    }
    free(cal->anos);
    free(cal);
}

static void printHora(HORA hora){
    if(!hora) return;
    for(GSList *cur = hora->posts; cur; cur = g_slist_next(cur)){
        printf("\t\t\t\tPost: %ld\n",post_get_id((void*) cur->data));
    }
}

static void printDia(DIA dia){
    if(!dia) return;
    for(int i=0; i<24; i++){
        printf("\t\t\tHora: %d\n",i);
        printHora(dia->horas[i]);
    }
}

static void printMes(MES mes){
    if(!mes) return;
    for(int i=0; i<mes->nDias; i++){
        printf("\t\tDia: %d\n",i);
        printDia(mes->dias[i]);
    }
}

static void printAno(ANO ano){
    if(!ano) return;
    for(int i=0; i<12;i++){
        printf("\tMes: %d\n",i);
        printMes(ano->meses[i]);
    }
}
void printCalendario(CALENDARIO cal){
    for(int i=0; i< cal->nAnos; i++){
        printf("Ano: %d\n",i);
        printAno(cal->anos[i]);
    }
}
