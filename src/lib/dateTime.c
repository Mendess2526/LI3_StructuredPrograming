#include "dateTime.h"
#include <stdlib.h>

/** Macro para compara dois inteiros positivos */
#define INT_CMP(a,b) ((a > b) - (a < b))

struct _dateTime{
    int ano;
    int mes;
    int dia;
    int horas;
    int minutos;
    int segundos;
    int milissegundos;
};

DATETIME dateTime_create(int ano, int mes, int dia, int horas, int minutos, int segundos, int milissegundos){
    DATETIME d = (DATETIME) malloc (sizeof (struct _dateTime));
    d->ano = ano;
    d->mes = mes;
    d->dia = dia;
    d->horas = horas;
    d->minutos = minutos;
    d->segundos = segundos;
    d->milissegundos = milissegundos;
    return d;
}

int dateTime_get_ano(DATETIME d){
    return d->ano;
}

int dateTime_get_mes(DATETIME d){
    return d->mes;
}

int dateTime_get_dia(DATETIME d){
    return d->dia;
}

int dateTime_get_horas(DATETIME d){
    return d->horas;
}

int dateTime_get_minutos(DATETIME d){
    return d->minutos;
}

int dateTime_get_segundos(DATETIME d){
    return d->segundos;
}

int dateTime_get_milissegundos(DATETIME d){
    return d->milissegundos;
}

void dateTime_destroy(DATETIME d){
    free(d);
}

int dateTime_compare(DATETIME dataA, DATETIME dataB){
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
