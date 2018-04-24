#ifndef __DATE_TIME_H__
#define __DATE_TIME_H__

/**
 * @file
 * Módulo que define um dateTime. Esta estrutura representa uma data e hora.
 */
#include "types.h"

/** Macro para obter a data mais antiga representavel */
#define dateTime_get_epoch() (dateTime_create(1901,11,1,20,45,52,0))

/** Macro para obter a data mais futura representavel */
#define dateTime_get_year2038() (dateTime_create(2038,0,18,3,14,7,0))

 /**
 * Cria uma data.
 * @param year O ano da data.
 * @param month O mês da data.
 * @param day O dia da data.
 * @param hours As horas da data.
 * @param minutes Os minutos da data.
 * @param seconds Os segundos da data.
 * @param milisseconds Os milissegundos da data.
 * @returns Uma data.
 */
DATETIME dateTime_create(int year,
                        int month,
                        int day,
                        int hours,
                        int minutes,
                        int seconds,
                        int milisseconds);

 /**
 * Retorna o ano da data.
 * @param d Uma data.
 * @returns O ano da data.
 */
int dateTime_get_year(DATETIME d);

 /**
 * Retorna o mês da data.
 * @param d Uma data.
 * @returns O mês da data.
 */
int dateTime_get_month(DATETIME d);

 /**
 * Retorna o dia da data.
 * @param d Uma data.
 * @returns O dia da data.
 */
int dateTime_get_day(DATETIME d);

 /**
 * Retorna as horas da data.
 * @param d Uma data.
 * @returns As horas da data.
 */
int dateTime_get_hours(DATETIME d);

 /**
 * Retorna os minutos da data.
 * @param d Uma data.
 * @returns Os minutos da data.
 */
int dateTime_get_minutes(DATETIME d);

 /**
 * Retorna os segundos da data.
 * @param d Uma data.
 * @returns Os segundos da data.
 */
int dateTime_get_seconds(DATETIME d);

 /**
 * Retorna os milisegundos da data.
 * @param d Uma data.
 * @returns Os milisegundos da data.
 */
int dateTime_get_milisseconds(DATETIME d);

 /**
 * Liberta a memória ocupada pela data.
 * @param d Uma data.
 */
void dateTime_destroy(DATETIME d);

 /**
 * Compara duas datas.
 * @param dataA Uma data.
 * @param dataB Uma data.
 * @returns Um número negativo se a primeira data for mais antiga, um número
 *          positivo se a primeira data for mais recente ou 0 se forem iguais.
 */
int dateTime_compare(DATETIME dataA, DATETIME dataB);

#endif /* __DATE_TIME_H__ */
