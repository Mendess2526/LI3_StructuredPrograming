#ifndef __DATE_TIME_H__
#define __DATE_TIME_H__

#include "types.h"

 /**
 *Cria uma data. 
 * @param ano O ano da data. 
 * @param mes O mês da data.
 * @param dia O dia da data.
 * @param horas As horas da data.
 * @param minutos Os minutos da data.
 * @param segundos Os segundos da data.
 * @param milissegundos Os milissegundos da data.
 * @returns Uma data. 
 */
DATETIME dateTime_create(int ano,
                        int mes,
                        int dia,
                        int horas,
                        int minutos,
                        int segundos,
                        int milissegundos);

 /**
 * Retorna o ano da data.
 * @param d Uma data.
 * @returns O ano da data.
 */
int dateTime_get_ano(DATETIME d);

 /**
 * Retorna o mês da data.
 * @param d Uma data.
 * @returns O mês da data.
 */
int dateTime_get_mes(DATETIME d);

 /**
 * Retorna o dia da data.
 * @param d Uma data.
 * @returns O dia da data.
 */
int dateTime_get_dia(DATETIME d);

 /**
 * Retorna as horas da data.
 * @param d Uma data.
 * @returns As horas da data.
 */
int dateTime_get_horas(DATETIME d);

 /**
 * Retorna os minutos da data.
 * @param d Uma data.
 * @returns Os minutos da data.
 */
int dateTime_get_minutos(DATETIME d);

 /**
 * Retorna os segundos da data.
 * @param d Uma data.
 * @returns Os segundos da data.
 */
int dateTime_get_segundos(DATETIME d);

 /**
 * Retorna os milisegundos da data.
 * @param d Uma data.
 * @returns Os milisegundos da data.
 */
int dateTime_get_milissegundos(DATETIME d);

 /**
 * Liberta a memória ocupada pela data.
 * @param d Uma data.
 */
void dateTime_destroy(DATETIME d);

 /**
 * Compara duas datas.
 * @param dataA Uma data.
 * @param dataB Uma data
 * @returns Um número negativo se a primeira data for mais antiga, um número positivo se a primeira data for mais recente ou 0 se forem iguais.
 */
int dateTime_compare(DATETIME dataA, DATETIME dataB);

#endif /*__DATE_TIME_H__*/