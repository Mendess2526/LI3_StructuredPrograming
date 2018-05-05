#ifndef __DATE_TIME_INTERVAL_H__
#define __DATE_TIME_INTERVAL_H__

/**
 * @file
 * \brief Módulo que define um dateTimeInterval. Esta estrutura representa
 *  um intervalo de tempo.
 */
#include "types.h"

/**
 * Cria um intervalo de tempo.
 * @param from A data de início.
 * @param to A data do fim.
 * @returns Um intervalo de tempo.
 */
DATETIME_INTERVAL dateTime_interval_create(DATETIME from, DATETIME to);

/**
 * Retorna a data de início do intervalo de tempo.
 * @param dti Um intervalo de tempo.
 * @returns Data de início do intervalo de tempo.
 */
DATETIME dateTime_interval_from(DATETIME_INTERVAL dti);

/**
 * Retorna a data de fim do intervalo de tempo.
 * @param dti Um intervalo de tempo.
 * @returns Data de fim do intervalo de tempo.
 */
DATETIME dateTime_interval_to(DATETIME_INTERVAL dti);

/**
 * Verifica se uma data pertence a um intervalo de tempo.
 * @param dti Um intervalo de tempo.
 * @param d Uma data.
 * @retuns 1 se pertence ao intervalo, 0 caso contrário. 
 */
int dateTime_interval_is_between(DATETIME_INTERVAL dti, DATETIME d);

/**
 * Liberta a memória ocupada pelo intervalo de tempo.
 * @param dti Um intervalo de tempo.
 */
void dateTime_interval_destroy(DATETIME_INTERVAL dti);

/**
 * Liberta a memória ocupada pelo intervalo de tempo e pelas datas.
 * @param dti Um intervalo de tempo.
 */
void dateTime_interval_destroy_full(DATETIME_INTERVAL dti);

#endif /* __DATE_TIME_INTERVAL_H__ */
