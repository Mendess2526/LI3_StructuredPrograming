#include "calendario.h"
#include "dateTime.h"
#include "post.h"
#include <glib.h>

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
    DIA *dias;
} *MES;

typedef struct _ano{
    MES *meses;
} *ANO;

struct _calendario{
    ANO *anos;
};

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
    d->horas = (HORA *) malloc(sizeof(struct _hora)*24);
    return d;
}

static MES mes_create(){
    MES m = (MES) malloc(sizeof(struct _mes));
    m->dias = (DIA *) malloc(sizeof(struct _dia)*31);
    return m;
}

static ANO ano_create(){
    ANO a = (ANO) malloc(sizeof(struct _ano));
    a->meses = (MES *) malloc(sizeof(struct _mes)*12);
    return a;
}

CALENDARIO calendario_create(){
    CALENDARIO c = (CALENDARIO) malloc(sizeof(struct _calendario));
    c->anos = (ANO *) malloc(sizeof(struct _ano)*10);
    return c;
}


static void dia_add_post(DIA dia, DATETIME d, POST post){
    int hora = dateTime_get_horas(d);
    hora_add_post(dia->horas[hora], post);
}

static void mes_add_post(MES mes, DATETIME d, POST post){
    int dia = dateTime_get_dia(d);
    dia_add_post(mes->dias[dia], d, post);
}

static void ano_add_post(ANO ano, DATETIME d, POST post){
    int mes = dateTime_get_mes(d);
    mes_add_post(ano->meses[mes], d, post);
}

void calendario_add_post(CALENDARIO cal, POST post){
    DATETIME d = post_get_date(post);
    int ano = dateTime_get_ano(d);
    ano_add_post(cal->anos[ano], d, post);
}
