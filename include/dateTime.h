#ifndef __DATE_TIME_H__
#define __DATE_TIME_H__

typedef struct _dateTime *DATETIME;

DATETIME dateTime_create(int ano,
                        int mes,
                        int dia,
                        int horas,
                        int minutos,
                        int segundos,
                        int milissegundos);

int dateTime_get_ano(DATETIME d);

int dateTime_get_mes(DATETIME d);

int dateTime_get_dia(DATETIME d);

int dateTime_get_horas(DATETIME d);

int dateTime_get_minutos(DATETIME d);

int dateTime_get_segundos(DATETIME d);

int dateTime_get_milissegundos(DATETIME d);

void dateTime_destroy(DATETIME d);

int dateTime_compare(DATETIME dataA, DATETIME dataB);

#endif /*__DATE_TIME_H__*/