#include "calendario.h"
#include "dateTime.h"
#include "post.h"

#include <string.h>

/** Macro que converte um ano, no indice do array */
#define ANO2INDEX(year) ((year)-2008 > cal->nYears-1 ? cal->nYears-1 : ((year)-2008 < 0 ? 0 : (year)-2008))


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
    int nYears;
    YEAR *years;
    CalCmpFunc compareFunc;
    CalFreeFunc freeFunc;
};

/**
 * \brief Devolve o número de dias que um mês \p m (0-11) tem.
 * 31 dias: [0, 2, 4, 6, 7, 9, 11]
 * 30 dias: [3, 5, 8, 10]
 * 29 dias: [1]
 * @param m Mes
 */
static int nrDays (int m);
/**
 * Cria uma "hora", que é constituida por uma lista de posts
 * @returns instância de \s HOUR
 */
static HOUR hour_create();
/**
 * Cria um dia, que é constituido por 24 \s HOUR
 * @returns instância de \s DIA
 */
static DAY day_create();
/**
 * Cria um mẽs, que é constituido por \p nDays dias.
 * @param nDays O número de dias do mês
 * @retuns instância de \s MONTH
 */
static MONTH month_create(int nDays);
/**
 * Cria um ano, que é constituido por 12 \s MONTH.
 * @returns instância de \s YEAR
 */
static YEAR year_create();
/**
 * Adiciona um post a uma hora.
 * @param h hora onde adicionar
 * @param post post a adicionar
 * @param compareFunc função de comparação para ordenar os posts
 *                    cronológicamente
 */
static inline void hour_add_post(HOUR h, void* post, CalCmpFunc compareFunc);
/**
 * Adiciona um post a um dia.
 * @param day dia onde adicionar
 * @param d data do post
 * @param post post a adicionar
 * @param compareFunc função de comparação para ordenar os posts
 *                    cronológicamente
 */
static void day_add_post(DAY day, DATETIME d, void* post, CalCmpFunc compareFunc);
/**
 * Adiciona um post a um mês.
 * @param month mês onde adicionar
 * @param d data do post
 * @param post post a adicionar
 * @param compareFunc função de comparação para ordenar os posts
 *                    cronológicamente
 */
static void month_add_post(MONTH month, DATETIME d, void* post, CalCmpFunc compareFunc);
/**
 * Adiciona um post a um ano.
 * @param year ano onde adicionar
 * @param d data do post
 * @param post post a adicionar
 * @param compareFunc função de comparação para ordenar os posts
 *                    cronológicamente
 */
static void year_add_post(YEAR year, DATETIME d, void* post, CalCmpFunc compareFunc);

/**
 * Itera sobre os posts de uma hora por ordem cronologica.
 * @param hour Hora onde iterar
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static inline int hour_iterate_forward(HOUR hour, void *data, CalFunc calFunc);
/**
 * Itera sobre os posts de um dia por ordem cronologica.
 * @param day Dia onde iterar
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static inline int day_iterate_forward(DAY day, void *data, CalFunc calFunc);
/**
 * Itera sobre os posts de um mês por ordem cronologica.
 * @param month Mês onde iterar
 * @param from Data de onde a iteração começa
 * @param to Data até onde a iteração continua
 * @param isStartM 1 se este mês é o primeiro do intervalo de tempo
 * @param isEndM 1 se este mês é o ultimo do intervalo de tempo
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static inline int month_iterate_forward(MONTH month, DATETIME from, DATETIME to, int isStartM, int isEndM, void* data, CalFunc calFunc);
/**
 * Itera sobre os posts de um ano por ordem cronologica.
 * @param year Ano onde iterar
 * @param from Data de onde a iteração começa
 * @param to Data até onde a iteração continua
 * @param isStartY 1 se este ano é o primeiro do intervalo de tempo
 * @param isEndY 1 se este ano é o ultimo do intervalo de tempo
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static inline int year_iterate_forward(YEAR year, DATETIME from, DATETIME to, int isStartY, int isEndY, void* data, CalFunc calFunc);
/**
 * Itera sobre os posts de um calendario por ordem cronologica.
 * @param hour Hora onde iterar
 * @param from Data de onde a iteração começa
 * @param to Data até onde a iteração continua
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static void calendario_iterate_forward(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CalFunc calFunc);

/**
 * Itera sobre os posts de uma hora por ordem cronologica inversa.
 * @param hour Hora onde iterar
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static inline int hour_iterate_backwards(HOUR hour, void *data, CalFunc calFunc);
/**
 * Itera sobre os posts de um dia por ordem cronologica inversa.
 * @param day Dia onde iterar
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static inline int day_iterate_backwards(DAY day, void *data, CalFunc calFunc);
/**
 * Itera sobre os posts de um mês por ordem cronologica inversa.
 * @param month Mês onde iterar
 * @param from Data de onde a iteração começa
 * @param to Data até onde a iteração continua
 * @param isStartM 1 se este mês é o primeiro do intervalo de tempo
 * @param isEndM 1 se este mês é o ultimo do intervalo de tempo
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static inline int month_iterate_backwards(MONTH month, DATETIME from, DATETIME to, int isStartM, int isEndM, void* data, CalFunc calFunc);
/**
 * Itera sobre os posts de um ano por ordem cronologica inversa.
 * @param year Ano onde iterar
 * @param from Data de onde a iteração começa
 * @param to Data até onde a iteração continua
 * @param isStartY 1 se este ano é o primeiro do intervalo de tempo
 * @param isEndY 1 se este ano é o ultimo do intervalo de tempo
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static inline int year_iterate_backwards(YEAR year, DATETIME from, DATETIME to, int isStartY, int isEndY, void* data, CalFunc calFunc);
/**
 * Itera sobre os posts de um calendario por ordem cronologica inversa.
 * @param hour Hora onde iterar
 * @param from Data de onde a iteração começa
 * @param to Data até onde a iteração continua
 * @param data informação do utilizador passada a \p calFunc
 * @param calFunc Função que será aplicada a todos os elementos
 * @returns 1 se a iteração deve continuar, 0 caso contrário.
 */
static void calendario_iterate_backwards(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CalFunc calFunc);

/**
 * Liberta a memória ocupada por uma hora
 * @param h Instância a libertar
 * @param freeFunc função que liberta os elementos da estrutura
 */
static void hour_destroy(HOUR h, CalFreeFunc freeFunc);
/**
 * Liberta a memória ocupada por um dia
 * @param d Instância a libertar
 * @param freeFunc função que liberta os elementos da estrutura
 */
static void day_destroy(DAY d, CalFreeFunc freeFunc);
/**
 * Liberta a memória ocupada por um mês
 * @param m Instância a libertar
 * @param freeFunc função que liberta os elementos da estrutura
 */
static void month_destroy(MONTH m, CalFreeFunc freeFunc);
/**
 * Liberta a memória ocupada por um ano
 * @param y Instância a libertar
 * @param freeFunc função que liberta os elementos da estrutura
 */
static void year_destroy(YEAR y, CalFreeFunc freeFunc);

static int nrDays (int m){
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

CALENDARIO calendario_create(int nYears, CalCmpFunc compareFunc, CalFreeFunc freeFunc){
    CALENDARIO c = (CALENDARIO) malloc(sizeof(struct _calendario));
    c->nYears = nYears;
    c->years = (YEAR*) calloc(nYears, sizeof(struct _year*));
    c->compareFunc = compareFunc;
    c->freeFunc = freeFunc;
    return c;
}

static inline void hour_add_post(HOUR h, void* post, CalCmpFunc compareFunc){
    h->count += 1;
    h->posts = g_list_insert_sorted(h->posts, post, compareFunc);
    if(h->last==NULL) h->last = h->posts;
    while(h->last->next!=NULL) h->last = h->last->next;
}

static void day_add_post(DAY day, DATETIME d, void* post, CalCmpFunc compareFunc){
    int hour = dateTime_get_hours(d);
    if(day->hours[hour] == NULL) day->hours[hour] = hour_create();
    hour_add_post(day->hours[hour], post, compareFunc);
}

static void month_add_post(MONTH month, DATETIME d, void* post, CalCmpFunc compareFunc){
    int day = dateTime_get_day(d);
    if(month->days[day] == NULL) month->days[day] = day_create();
    day_add_post(month->days[day], d, post, compareFunc);
}

static void year_add_post(YEAR year, DATETIME d, void* post, CalCmpFunc compareFunc){
    int month = dateTime_get_month(d);
    if(year->months[month] == NULL)
        year->months[month] = month_create(nrDays(month));
    month_add_post(year->months[month], d, post, compareFunc);
}

void calendario_add_post(CALENDARIO cal, void* post, DATETIME d){
    int year = ANO2INDEX(dateTime_get_year(d));
    if(cal->years[year] == NULL) cal->years[year] = year_create();
    year_add_post(cal->years[year], d, post, cal->compareFunc);
}

static inline int hour_iterate_forward(HOUR hour, void* data, CalFunc calFunc){
    if(!hour) return 1;
    for(GList* cur = hour->last; cur != NULL; cur = cur->prev){
        if((*calFunc)(cur->data, data) == 0)
            return 0;
    }
    return 1;
}

static inline int day_iterate_forward(DAY day, void* data, CalFunc calFunc){
    if(!day) return 1;
    for(int i=0; i<24; i++){
        if(hour_iterate_forward(day->hours[i], data, calFunc) == 0)
            return 0;
    }
    return 1;
}

static inline int month_iterate_forward(MONTH month, DATETIME from, DATETIME to, int isStartM, int isEndM, void* data, CalFunc calFunc){
    if(!month) return 1;
    int fromD;
    int toD;
    switch(isStartM+isEndM){
        case 3: // Inicio e fim
            fromD = dateTime_get_day(from);
            toD = dateTime_get_day(to);
            break;
        case 2: // Inicio
            fromD = dateTime_get_day(from);
            toD = month->nDays-1;
            break;
        case 1: // Fim
            fromD = 0;
            toD = dateTime_get_day(to);
            break;
        default: // Nenhum
            fromD = 0;
            toD = month->nDays-1;
            break;
    }
    if(fromD <= toD){
        if(day_iterate_forward(month->days[fromD++], data, calFunc) == 0)
            return 0;
    }
    while(fromD <= toD){
        if(day_iterate_forward(month->days[fromD++], data, calFunc) == 0)
            return 0;
    }
    return 1;
}

static inline int year_iterate_forward(YEAR year, DATETIME from, DATETIME to, int isStartY, int isEndY, void* data, CalFunc calFunc){
    if(!year) return 1;
    int fromM;
    int toM;
    switch(isStartY+isEndY){
        case 3: // Inicio e fim
            fromM = dateTime_get_month(from);
            toM = dateTime_get_month(to);
            break;
        case 2: // Inicio
            fromM = dateTime_get_month(from);
            toM = 11;
            break;
        case 1: // Fim
            fromM = 0;
            toM = dateTime_get_month(to);
            break;
        default: // Nenhum
            fromM = 0;
            toM = 11;
            break;
    }

    if(isStartY && fromM <= toM){
        int isEndM = isEndY && fromM == toM;
        if(month_iterate_forward(year->months[fromM++], from, to, 2, isEndM, data, calFunc) == 0)
            return 0;
    }
    while(fromM <= toM){
        int isEndM = isEndY && fromM == toM;
        if(month_iterate_forward(year->months[fromM++], from, to, 0, isEndM, data, calFunc) == 0)
            return 0;
    }
    return 1;
}

static void calendario_iterate_forward(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CalFunc calFunc){
    if(!from || !to) return;
    int fromY = ANO2INDEX(dateTime_get_year(from));
    int toY = ANO2INDEX(dateTime_get_year(to));

    if(fromY <= toY){
        int isEndY = toY == fromY;
        if(year_iterate_forward(cal->years[fromY++], from, to, 2, isEndY, data, calFunc) == 0)
            return;
    }
    while(fromY <= toY){
        int isEndY = toY == fromY;
        if(year_iterate_forward(cal->years[fromY++], from, to, 0, isEndY, data, calFunc) == 0)
            break;
    }
}

static inline int hour_iterate_backwards(HOUR hour, void* data, CalFunc calFunc){
    if(!hour) return 1;
    for(GList* cur = hour->posts; cur != NULL; cur = cur->next){
        if((*calFunc)(cur->data, data) == 0)
            return 0;
    }
    return 1;
}

static inline int day_iterate_backwards(DAY day, void* data, CalFunc calFunc){
    if(!day) return 1;
    for(int i=23; i>=0; i--){
        if(hour_iterate_backwards(day->hours[i], data, calFunc) == 0)
            return 0;
    }
    return 1;
}

static inline int month_iterate_backwards(MONTH month, DATETIME from, DATETIME to, int isStartM, int isEndM, void* data, CalFunc calFunc){
    if(!month) return 1;
    int fromD;
    int toD;
    switch(isStartM+isEndM){
        case 3: // Inicio e fim
            fromD = dateTime_get_day(from);
            toD = dateTime_get_day(to);
            break;
        case 2: // Inicio
            fromD = dateTime_get_day(from);
            toD = 0;
            break;
        case 1: // Fim
            fromD = month->nDays-1;
            toD = dateTime_get_day(to);
            break;
        default: // Nenhum
            fromD = month->nDays-1;
            toD = 0;
            break;
    }
    if(fromD >= toD){
        if(day_iterate_backwards(month->days[fromD--], data, calFunc) == 0)
            return 0;
    }
    while(fromD >= toD){
        if(day_iterate_backwards(month->days[fromD--], data, calFunc) == 0)
            return 0;
    }
    return 1;
}

static inline int year_iterate_backwards(YEAR year, DATETIME from, DATETIME to, int isStartY, int isEndY, void* data, CalFunc calFunc){
    if(!year) return 1;
    int fromM;
    int toM;
    switch(isStartY+isEndY){
        case 3: // Inicio e fim
            fromM = dateTime_get_month(from);
            toM = dateTime_get_month(to);
            break;
        case 2: // Inicio
            fromM = dateTime_get_month(from);
            toM = 0;
            break;
        case 1: // Fim
            fromM = 11;
            toM = dateTime_get_month(to);
            break;
        default: // Nenhum
            fromM = 11;
            toM = 0;
            break;
    }

    if(isStartY && fromM >= toM){
        int isEndM = isEndY && fromM == toM;
        if(month_iterate_backwards(year->months[fromM--], from, to, 2, isEndM, data, calFunc) == 0)
            return 0;
    }
    while(fromM >= toM){
        int isEndM = isEndY && fromM == toM;
        if(month_iterate_backwards(year->months[fromM--], from, to, 0, isEndM, data, calFunc) == 0)
            return 0;
    }
    return 1;
}

static void calendario_iterate_backwards(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CalFunc calFunc){
    if(!from || !to) return;
    int fromY = ANO2INDEX(dateTime_get_year(from));
    int toY = ANO2INDEX(dateTime_get_year(to));

    if(fromY >= toY){
        int isEndY = toY == fromY;
        if(year_iterate_backwards(cal->years[fromY--], from, to, 2, isEndY, data, calFunc) == 0)
            return;
    }
    while(fromY >= toY){
        int isEndY = toY == fromY;
        if(year_iterate_backwards(cal->years[fromY--], from, to, 0, isEndY, data, calFunc) == 0)
            break;
    }
}

void calendario_iterate(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CalFunc calFunc){
    if(dateTime_compare(from,to) < 0)
        calendario_iterate_forward(cal,from, to, data, calFunc);
    else calendario_iterate_backwards(cal, from, to, data, calFunc);
}

static void hour_destroy(HOUR h, CalFreeFunc freeFunc){
    if(h==NULL) return;
    if(freeFunc) g_list_free_full(h->posts, freeFunc);
    else g_list_free(h->posts);
    free(h);
}

static void day_destroy(DAY d, CalFreeFunc freeFunc){
    if(d==NULL) return;
    for(int i=0; i<24; i++){
        hour_destroy(d->hours[i], freeFunc);
    }
    free(d->hours);
    free(d);
}

static void month_destroy(MONTH m, CalFreeFunc freeFunc){
    if(m==NULL) return;
    for(int i=0; i<(m->nDays); i++){
        day_destroy(m->days[i], freeFunc);
    }
    free(m->days);
    free(m);
}

static void year_destroy(YEAR y, CalFreeFunc freeFunc){
    if(y==NULL) return;
    for(int i=0; i<12; i++){
        month_destroy(y->months[i], freeFunc);
    }
    free(y->months);
    free(y);
}

void calendario_destroy(CALENDARIO cal){
    for(int i=0; i<(cal->nYears); i++){
        year_destroy(cal->years[i], cal->freeFunc);
    }
    free(cal->years);
    free(cal);
}

static void printHora(HOUR hour, CalPrintFunc printFuncion){
    if(!hour) return;
    for(GList *cur = hour->posts; cur; cur = g_list_next(cur)){
        (*printFuncion)(cur->data);
    }
}

static void printDia(DAY day, CalPrintFunc printFuncion){
    if(!day) return;
    for(int i=0; i<24; i++){
        printf("\t\t\tHora: %d\n",i);
        printHora(day->hours[i], printFuncion);
    }
}

static void printMes(MONTH month, CalPrintFunc printFuncion){
    if(!month) return;
    for(int i=0; i<month->nDays; i++){
        printf("\t\tDia: %d\n",i);
        printDia(month->days[i], printFuncion);
    }
}

static void printAno(YEAR year, CalPrintFunc printFuncion){
    if(!year) return;
    for(int i=0; i<12;i++){
        printf("\tMes: %d\n",i);
        printMes(year->months[i], printFuncion);
    }
}

void printCalendario(CALENDARIO cal, CalPrintFunc printFuncion){
    for(int i=0; i< cal->nYears; i++){
        printf("Ano: %d\n",i);
        printAno(cal->years[i], printFuncion);
    }
}
