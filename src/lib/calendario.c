#include "calendario.h"
#include "dateTime.h"
#include "post.h"
#include <glib.h>
#include <string.h>

/** Macro para compara dois inteiros positivos */
#define INT_CMP(a,b) ((a > b) - (a < b))

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
};

static HORA hora_create();
static inline void hora_add_post(HORA h, POST p);
static DIA dia_create();
static MES mes_create(int nDias);
static ANO ano_create();
static void dia_add_post(DIA dia, DATETIME d, POST post);
static void mes_add_post(MES mes, DATETIME d, POST post);
static void ano_add_post(ANO ano, DATETIME d, POST post);
static inline GSList* hora_get_post_ids(HORA hora, GSList * ids);
static inline GSList* dia_get_post_ids(DIA dia, GSList *ids);
static inline GSList* mes_get_post_ids(MES mes, Date from, Date to, GSList *ids);
static inline GSList* ano_get_post_ids(ANO ano, Date from, Date to, GSList *ids);
static void dia_destroy(DIA d);
static void mes_destroy(MES m);
static void ano_destroy(ANO a);
static int nrDias (int m);


gint timeCompare(gconstpointer a, gconstpointer b){
    DATETIME dataA = post_get_date((POST) a);
    DATETIME dataB = post_get_date((POST) b);
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

static inline void hora_add_post(HORA h, POST p){
    h->count += 1;
    h->posts = g_slist_insert_sorted(h->posts, p, timeCompare);
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

CALENDARIO calendario_create(int nAnos){
    CALENDARIO c = (CALENDARIO) malloc(sizeof(struct _calendario));
    c->nAnos = nAnos;
    c->anos = (ANO *) calloc(nAnos, sizeof(struct _ano *));
    return c;
}

static void dia_add_post(DIA dia, DATETIME d, POST post){
    int hora = dateTime_get_horas(d);
    if(dia->horas[hora] == NULL) dia->horas[hora] = hora_create();
    hora_add_post(dia->horas[hora], post);
}

static void mes_add_post(MES mes, DATETIME d, POST post){
    int dia = dateTime_get_dia(d);
    if(mes->dias[dia] == NULL) mes->dias[dia] = dia_create();
    dia_add_post(mes->dias[dia], d, post);
}

static int nrDias (int m){
    if(m == 3 || m == 5 || m == 8 || m == 10) return 30;
    if(m == 1) return 29;
    return 31;
}

static void ano_add_post(ANO ano, DATETIME d, POST post){
    int mes = dateTime_get_mes(d);
    if(ano->meses[mes] == NULL)
        ano->meses[mes] = mes_create(nrDias(mes));
    mes_add_post(ano->meses[mes], d, post);
}

void calendario_add_post(CALENDARIO cal, POST post){
    DATETIME d = post_get_date(post);
    int ano = dateTime_get_ano(d);
    if(cal->anos[ano-2008] == NULL) cal->anos[ano] = ano_create();
    ano_add_post(cal->anos[ano], d, post);
}

static inline GSList* hora_get_post_ids(HORA hora, GSList * ids){
    return g_slist_concat(ids,hora->posts);
}

static inline GSList* dia_get_post_ids(DIA dia, GSList *ids){
    for(int i=0; i<24; i++){
        ids = hora_get_post_ids(dia->horas[i], ids);
    }
    return ids;
}

static inline GSList* mes_get_post_ids(MES mes, Date from, Date to, GSList *ids){
    int fromD = get_day(from);
    int toD = get_day(to);
    while(fromD < toD)
        ids = dia_get_post_ids(mes->dias[fromD++], ids);

    return ids;
}

static inline GSList* ano_get_post_ids(ANO ano, Date from, Date to, GSList *ids){
    int fromM = get_month(from);
    int toM = get_month(to);
    while(fromM <= toM)
        ids = mes_get_post_ids(ano->meses[fromM++], from, to, ids);

    return ids;
}

long *calendario_get_ids(CALENDARIO cal, Date from, Date to){
    int fromY = get_year(from);
    int toY = get_year(to);
    GSList * ids = NULL;
    while(fromY <= toY){
        ids = ano_get_post_ids(cal->anos[fromY++], from, to, ids);
    }
    int len = g_slist_length(ids);
    long *idArray = malloc(sizeof(long)*len);
    int i;
    GSList *cur;
    for(i = 0, cur = ids; i<len && cur; i++){
        idArray[i] = post_get_id((POST) cur->data);
        cur = g_slist_next(cur);
    }
    g_slist_free(ids);
    return idArray;
}

static void hora_destroy(HORA h){
    g_slist_free_full(h->posts, post_destroy_generic);
    free(h);
}

static void dia_destroy(DIA d){
    for(int i=0; i<24; i++){
        hora_destroy(d->horas[i]);
    }
    free(d);
}

static void mes_destroy(MES m){
    for(int i=0; i<(m->nDias); i++){
        dia_destroy(m->dias[i]);
    }
    free(m);
}

static void ano_destroy(ANO a){
    for(int i=0; i<12; i++){
        mes_destroy(a->meses[i]);
    }
    free(a);
}

void calendario_destroy(CALENDARIO cal){
    for(int i=0; i<(cal->nAnos); i++){
        ano_destroy(cal->anos[i]);
    }
    free(cal);
}
