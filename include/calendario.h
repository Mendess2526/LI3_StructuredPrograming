#ifndef __CALENDARIO_H__
#define __CALENDARIO_H__

/**
 * @file
 * Módulo que define o calendário. Este é uma estrutura que permite guardar
 * valores arbitrários associados a uma data.
 */
#include "post.h"
#include "date.h"
#include "types.h"

#include <glib.h>

 /**
 * Cria um calendário.
 * @param nYears Número de anos que o calendário tem.
 * @param compareFunc Função que compara datas dos elementos inseridos.
 * @param freeFunc Função que liberta a memória ocupada pelos elementos inseridos.
 */
CALENDARIO calendario_create(int nYears, CCompareFunc compareFunc, CFreeFunc freeFunc);

 /**
 * Adiciona um post no calendário.
 * @param cal Um calendário.
 * @param post O post a adicionar.
 * @param d A data do post.
 */
void calendario_add_post(CALENDARIO cal, void* post, DATETIME d);

 /**
 * Itera o calendário.
 * @param cal Um calendário.
 * @param from A data do inicio.
 * @param to A data do fim.
 * @param data Informação passada a calFunc.
 * @param calFunc Função chamada para cada elemento entre as datas.
 */
void calendario_iterate(CALENDARIO cal, DATETIME from, DATETIME to, void* data, CFunc calFunc);

 /**
 * Liberta a memória ocupada pelo calendário.
 * @param cal Um calendário.
 */
void calendario_destroy(CALENDARIO cal);

/* ------------- PRINTING --------------------- */

void printCalendario(CALENDARIO cal, CPrintFunction printFunction);

#endif /* __CALENDARIO_H__ */
