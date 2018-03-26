#include "dateTime.h"

struct dateTime{
    int ano;
    int mes;
    int dia;
    int horas;
    int minutos;
    int segundos;
    int milissegundos;
};

DATETIME dateTime_create(int ano, int mes, int dia, int horas, int minutos, int segundos, int milissegundos){
    DATETIME d = DATETIME malloc (sizeof (struct _dateTime));
    d->ano = ano;
    d->mes = mes;
    d->dia = dia;
    d->horas = horas;
    d->minutos = minutos;
    d->segundos = segundos;
    d->milissegundos = milissegundos;
    return d;
}








