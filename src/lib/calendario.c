#include "calendario.h"
#include "dateTime.h"
#include "post.h"
#include <string.h>

#define ANO2INDEX(year) (year-2008 > cal->nAnos-1 ? cal->nAnos-1 : (year-2008 < 0 ? 0 : year-2008))


typedef GList * POSTS;

typedef struct _hour{
    int count;
    POSTS posts;
    GList* last;
} *HOUR;

typedef struct _day{
    HOUR *hours;
} *DAY;

typedef struct _month{
    int nDays;
    DAY *days;
} *MONTH;

typedef struct _year{
    MONTH *months;
} *YEAR;

struct _calendario{
    int nAnos;
    YEAR *years;
    CCompareFunc compareFunc;
    CFreeFunc freeFunc;
};

static int nrDias (int m);

static HOUR hour_create();
static DAY day_create();
static MONTH month_create(int nDays);
static YEAR year_create();

static inline void hour_add_post(HOUR h, void* p, CCompareFunc compareFunc);
static void day_add_post(DAY day, DATETIME d, void* post, CCompareFunc compareFunc);
static void month_add_post(MONTH month, DATETIME d, void* post, CCompareFunc compareFunc);
static void year_add_post(YEAR year, DATETIME d, void* post, CCompareFunc compareFunc);

static inline void hour_iterate_forward(HOUR hour, void *data, CFunc calFunc);
static inline void day_iterate_forward(DAY day, void *data, CFunc calFunc);
static inline void month_iterate_forward(MONTH month, DATETIME from, DATETIME to, int sameMonth, void* data, CFunc calFunc);
static inline void year_iterate_forward(YEAR year, DATETIME from, DATETIME to, int sameYear, void* data, CFunc calFunc);

static void calendario_iterate_backwards(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CFunc calFunc);

static void hour_destroy(HOUR h, CFreeFunc freeFunc);
static void day_destroy(DAY d, CFreeFunc freeFunc);
static void month_destroy(MONTH m, CFreeFunc freeFunc);
static void year_destroy(YEAR a, CFreeFunc freeFunc);

static int nrDias (int m){
    if(m == 3 || m == 5 || m == 8 || m == 10) return 30;
    if(m == 1) return 29;
    return 31;
}


static HOUR hour_create(){
    HOUR h = (HOUR) malloc(sizeof(struct _hour));
    h->count = 0;
    h->posts = NULL;
    h->last = NULL;
    return h;
}

static DAY day_create(){
    DAY d = (DAY) malloc(sizeof(struct _day));
    d->hours = (HOUR*) calloc(24, sizeof(struct _hour *));
    return d;
}

static MONTH month_create(int nDays){
    MONTH m = (MONTH) malloc(sizeof(struct _month));
    m->nDays = nDays;
    m->days = (DAY*) calloc(nDays, sizeof(struct _day *));
    return m;
}

static YEAR year_create(){
    YEAR a = (YEAR) malloc(sizeof(struct _year));
    a->months = (MONTH*) calloc(12, sizeof(struct _month *));
    return a;
}

CALENDARIO calendario_create(int nAnos, CCompareFunc compareFunc, CFreeFunc freeFunc){
    CALENDARIO c = (CALENDARIO) malloc(sizeof(struct _calendario));
    c->nAnos = nAnos;
    c->years = (YEAR*) calloc(nAnos, sizeof(struct _year*));
    c->compareFunc = compareFunc;
    c->freeFunc = freeFunc;
    return c;
}

static inline void hour_add_post(HOUR h, void* post, CCompareFunc compareFunc){
    h->count += 1;
    h->posts = g_list_insert_sorted(h->posts, post, compareFunc);
    if(h->last==NULL) h->last = h->posts;
    while(h->last->next!=NULL) h->last = h->last->next; 
}

static void day_add_post(DAY day, DATETIME d, void* post, CCompareFunc compareFunc){
    int hour = dateTime_get_hours(d);
    if(day->hours[hour] == NULL) day->hours[hour] = hour_create();
    hour_add_post(day->hours[hour], post, compareFunc);
}

static void month_add_post(MONTH month, DATETIME d, void* post, CCompareFunc compareFunc){
    int day = dateTime_get_day(d);
    if(month->days[day] == NULL) month->days[day] = day_create();
    day_add_post(month->days[day], d, post, compareFunc);
}

static void year_add_post(YEAR year, DATETIME d, void* post, CCompareFunc compareFunc){
    int month = dateTime_get_month(d);
    if(year->months[month] == NULL)
        year->months[month] = month_create(nrDias(month));
    month_add_post(year->months[month], d, post, compareFunc);
}

void calendario_add_post(CALENDARIO cal, void* post, DATETIME d){
    int year = ANO2INDEX(dateTime_get_year(d));
    if(cal->years[year] == NULL) cal->years[year] = year_create();
    year_add_post(cal->years[year], d, post, cal->compareFunc);
}

static inline void hour_iterate_forward(HOUR hour, void* data, CFunc calFunc){
    if(!hour) return;
    for(GList* cur = hour->last; cur != NULL; cur = cur->prev){
        (*calFunc)(cur->data, data);
    }
}

static inline void day_iterate_forward(DAY day, void* data, CFunc calFunc){
    if(!day) return;
    for(int i=0; i<24; i++)
        hour_iterate_forward(day->hours[i], data, calFunc);
}

static inline void month_iterate_forward(MONTH month, DATETIME from, DATETIME to, int sameMonth, void* data, CFunc calFunc){
    if(!month) return;
    int fromD = dateTime_get_day(from);
    int toD = sameMonth ? dateTime_get_day(to) : month->nDays-1;
    while(fromD <= toD)
        day_iterate_forward(month->days[fromD++], data, calFunc);
}

static inline void year_iterate_forward(YEAR year, DATETIME from, DATETIME to, int sameYear, void* data, CFunc calFunc){
    if(!year) return;
    int fromM = dateTime_get_month(from);
    int toM = sameYear ? dateTime_get_month(to) : 11;
    int sameMonth = sameYear && fromM == toM;
    while(fromM <= toM)
        month_iterate_forward(year->months[fromM++], from, to, sameMonth, data, calFunc);
}

static void calendario_iterate_forward(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CFunc calFunc){
    if(!from || !to) return;
    int fromY = ANO2INDEX(dateTime_get_year(from));
    int toY = ANO2INDEX(dateTime_get_year(to));
    int sameYear = fromY == toY;
    while(fromY < cal->nAnos && fromY <= toY)
        year_iterate_forward(cal->years[fromY++], from, to, sameYear, data, calFunc);
}

static inline void hour_iterate_backwards(HOUR hour, void* data, CFunc calFunc){
    if(!hour) return;
    g_list_foreach(hour->posts, calFunc, data);
}

static inline void day_iterate_backwards(DAY day, void* data, CFunc calFunc){
    if(!day) return;
    for(int i=0; i<24; i++)
        hour_iterate_forward(day->hours[i], data, calFunc);
}

static inline void month_iterate_backwards(MONTH month, DATETIME from, DATETIME to, int sameMonth, void* data, CFunc calFunc){
    if(!month) return;
    int fromD = dateTime_get_day(from);
    int toD = sameMonth ? dateTime_get_day(to) : 0;
    while(toD <= fromD)
        day_iterate_forward(month->days[fromD--], data, calFunc);
}

static inline void year_iterate_backwards(YEAR year, DATETIME from, DATETIME to, int sameYear, void* data, CFunc calFunc){
    if(!year) return;
    int fromM = dateTime_get_month(from);
    int toM = sameYear ? dateTime_get_month(to) : 0;
    int sameMonth = sameYear && fromM == toM;
    while(toM <= fromM)
        month_iterate_forward(year->months[fromM--], from, to, sameMonth, data, calFunc);
}

static void calendario_iterate_backwards(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CFunc calFunc){
    if(!from || !to) return;
    int fromY = ANO2INDEX(dateTime_get_year(from));
    int toY = ANO2INDEX(dateTime_get_year(to));
    int sameYear = fromY == toY;
    while(toY <= fromY)
        year_iterate_forward(cal->years[fromY--], from, to, sameYear, data, calFunc);
}

void calendario_iterate(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CFunc calFunc){
    if(dateTime_compare(from,to) < 0)
        calendario_iterate_forward(cal,from, to, data, calFunc);
    else calendario_iterate_backwards(cal, from, to, data, calFunc);
}

static void hour_destroy(HOUR h, CFreeFunc freeFunc){
    if(h==NULL) return;
    if(freeFunc) g_list_free_full(h->posts, freeFunc);
    else g_list_free(h->posts);
    free(h);
}

static void day_destroy(DAY d, CFreeFunc freeFunc){
    if(d==NULL) return;
    for(int i=0; i<24; i++){
        hour_destroy(d->hours[i], freeFunc);
    }
    free(d->hours);
    free(d);
}

static void month_destroy(MONTH m, CFreeFunc freeFunc){
    if(m==NULL) return;
    for(int i=0; i<(m->nDays); i++){
        day_destroy(m->days[i], freeFunc);
    }
    free(m->days);
    free(m);
}

static void year_destroy(YEAR a, CFreeFunc freeFunc){
    if(a==NULL) return;
    for(int i=0; i<12; i++){
        month_destroy(a->months[i], freeFunc);
    }
    free(a->months);
    free(a);
}

void calendario_destroy(CALENDARIO cal){
    for(int i=0; i<(cal->nAnos); i++){
        year_destroy(cal->years[i], cal->freeFunc);
    }
    free(cal->years);
    free(cal);
}

static void printHora(HOUR hour, CPrintFunction printFuncion){
    if(!hour) return;
    for(GList *cur = hour->posts; cur; cur = g_list_next(cur)){
        (*printFuncion)(cur->data);
    }
}

static void printDia(DAY day, CPrintFunction printFuncion){
    if(!day) return;
    for(int i=0; i<24; i++){
        printf("\t\t\tHora: %d\n",i);
        printHora(day->hours[i], printFuncion);
    }
}

static void printMes(MONTH month, CPrintFunction printFuncion){
    if(!month) return;
    for(int i=0; i<month->nDays; i++){
        printf("\t\tDia: %d\n",i);
        printDia(month->days[i], printFuncion);
    }
}

static void printAno(YEAR year, CPrintFunction printFuncion){
    if(!year) return;
    for(int i=0; i<12;i++){
        printf("\tMes: %d\n",i);
        printMes(year->months[i], printFuncion);
    }
}

void printCalendario(CALENDARIO cal, CPrintFunction printFuncion){
    for(int i=0; i< cal->nAnos; i++){
        printf("Ano: %d\n",i);
        printAno(cal->years[i], printFuncion);
    }
}
