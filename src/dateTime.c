#include "dateTime.h"

#include <stdlib.h>

/** Macro para compara dois inteiros positivos. */
#define INT_CMP(a, b) (((a) > (b)) - ((a) < (b)))

struct _dateTime{
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int seconds;
    int milisseconds;
};

DATETIME dateTime_create(int year,
                         int month,
                         int day,
                         int hours,
                         int minutes,
                         int seconds,
                         int milisseconds){
    DATETIME d = (DATETIME) malloc(sizeof(struct _dateTime));
    d->year = year;
    d->month = month;
    d->day = day;
    d->hours = hours;
    d->minutes = minutes;
    d->seconds = seconds;
    d->milisseconds = milisseconds;
    return d;
}

int dateTime_get_year(DATETIME d){
    return d->year;
}

int dateTime_get_month(DATETIME d){
    return d->month;
}

int dateTime_get_day(DATETIME d){
    return d->day;
}

int dateTime_get_hours(DATETIME d){
    return d->hours;
}

int dateTime_get_minutes(DATETIME d){
    return d->minutes;
}

int dateTime_get_seconds(DATETIME d){
    return d->seconds;
}

int dateTime_get_milisseconds(DATETIME d){
    return d->milisseconds;
}

void dateTime_destroy(DATETIME d){
    free(d);
}

int dateTime_compare(DATETIME dataA, DATETIME dataB){
    int c;
    c = INT_CMP(dataA->year, dataB->year);
    if(c) return c;
    c = INT_CMP(dataA->month, dataB->month);
    if(c) return c;
    c = INT_CMP(dataA->day, dataB->day);
    if(c) return c;
    c = INT_CMP(dataA->hours, dataB->hours);
    if(c) return c;
    c = INT_CMP(dataA->minutes, dataB->minutes);
    if(c) return c;
    c = INT_CMP(dataA->seconds, dataB->seconds);
    if(c) return c;
    c = INT_CMP(dataA->milisseconds, dataB->milisseconds);
    if(c) return c;
    return 0;
}