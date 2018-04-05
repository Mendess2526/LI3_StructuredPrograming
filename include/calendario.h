#ifndef __CALENDARIO_H__
#define __CALENDARIO_H__

#include "post.h"
#include "date.h"
#include "types.h"

#include <glib.h>

 /**
 * Cria um calendário.
 * @param nANos Número de anos que o calendário tem.
 * @param compareFunc ??
 * @param freeFunc ??
 */
CALENDARIO calendario_create(int nAnos, CCompareFunc compareFunc, CFreeFunc freeFunc);

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
 * @param data ??
 * @param calFunc ??
 */
void calendario_iterate(CALENDARIO cal, Date from, Date to, void* data, CFunc calFunc);

 /**
 * Liberta a memória ocupada pelo calendário.
 * @param cal
 */
void calendario_destroy(CALENDARIO cal);

 /**
 *
 * @param post
 */
void printCalendario(CALENDARIO cal, CPrintFunction printFunction);

#endif
