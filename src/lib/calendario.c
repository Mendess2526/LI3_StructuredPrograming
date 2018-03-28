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
static inline long* hora_get_post_ids(HORA h);
static DIA dia_create();
static MES mes_create(int nDias);
static ANO ano_create();
static void dia_add_post(DIA dia, DATETIME d, POST post);
static void mes_add_post(MES mes, DATETIME d, POST post);
static void ano_add_post(ANO ano, DATETIME d, POST post);
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

void getId(gpointer data, gpointer user_data){
    long id = post_get_id((POST) data);
    long *ids = (long *) user_data;
    int idx = (int) ids[0];
    ids[idx] = id;
    ids[0]++;
}

static inline long* hora_get_post_ids(HORA h){
    long *ids = (long *) malloc(sizeof(long)*h->count + 1);
    ids[0] = 1;
    g_slist_foreach(h->posts,getId,ids);
    return ids;
}

static DIA dia_create(){
    DIA d = (DIA) malloc(sizeof(struct _dia));
    d->horas = (HORA *) malloc(sizeof(struct _hora *)*24);
    memset(d->horas,0,sizeof(struct _hora *)*24);
    return d;
}

static MES mes_create(int nDias){
    MES m = (MES) malloc(sizeof(struct _mes));
    m->nDias = nDias;
    m->dias = (DIA *) malloc(sizeof(struct _dia *)*nDias);
    memset(m->dias,0,sizeof(struct _dia *)*nDias);
    return m;
}

static ANO ano_create(){
    ANO a = (ANO) malloc(sizeof(struct _ano));
    a->meses = (MES *) malloc(sizeof(struct _mes *)*12);
    memset(a->meses,0,sizeof(struct _mes *)*12);
    return a;
}

CALENDARIO calendario_create(int nAnos){
    CALENDARIO c = (CALENDARIO) malloc(sizeof(struct _calendario));
    c->nAnos = nAnos;
    c->anos = (ANO *) malloc(sizeof(struct _ano *)*nAnos);
    memset(c->anos,0,sizeof(struct _ano *)*nAnos);
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
    if(cal->anos[ano] == NULL) cal->anos[ano] = ano_create();
    ano_add_post(cal->anos[ano], d, post);
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