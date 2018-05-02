#ifndef __TYPES_H__
#define __TYPES_H__

 /**
 * @file
 * \brief Módulo que define os princípais tipos usados.
 */
#include <glib.h>

 /** Tipo abstrato de dados. */
typedef struct TCD_community * TAD_community;

 /**
 * Especifíca o tipo de função passada à TAD_community para comparar elementos desta.
 * @param a Elemento a.
 * @param b Elemento b.
 * @returns Um número positivo se a for maior que b, 0 se forem iguais ou um 
 *      número negativo se b for menor que a.
 */
typedef int (*ComCmpFunc)(const void* a, const void* b);

 /**
 * Especifíca o tipo de função passada à TAD_community para comparar elementos desta.
 * @param a Elemento a.
 * @param b Elemento b.
 * @param user_data Informação extra.
 * @returns Um número positivo se a for maior que b, 0 se forem iguais ou um
 *      número negativo se b for menor que a.
 */
typedef int (*ComGetValueFunc)(const void* a, const void* user_data);

 /**
 * Especifíca o tipo de função passada à TAD_community para filtrar elementos.
 * @param elem Elemento da TAD.
 * @param filter_data Informação do utilizador.
 * @returns 1 se passar no filtro, 0 caso contrário.
 */
typedef int (*ComFilterFunc) (void* elem, void* filter_data);

 /** Tipo abstrato de post. */
typedef struct _post * POST;

 /** Tipo abstrato de questão. */
typedef struct _question * QUESTION;

 /** Tipo abstrato de user. */
typedef struct _so_user * SO_USER;

 /** Tipo abstrato de resposta. */
typedef struct _answer * ANSWER;

 /** Tipo abstrato de DateTime. */
typedef struct _dateTime * DATETIME;

 /** Tipo abstrato de um par de DateTime. */
typedef struct _dateTime_interval * DATETIME_INTERVAL;

 /** Tipo abstrato de Calendário. */
typedef struct _calendario * CALENDARIO;

 /**
 * Especifíca o tipo de função passada ao calendário para operar sobre os elementos do mesmo.
 * @param elem Elemento do calendário.
 * @param user_data Informação do utilizador.
 * @returns 0 se a iteração sobre os elementos deve terminar, 1 caso contrário.
 */
typedef int (*CalFunc)(void* elem, void* user_data);

 /**
 * Especifíca o tipo da função chamada para cada elemento do calendário para 
 * libertar a memória ocupada por este.
 * @param data Elemento a destruir.
 */
typedef GDestroyNotify CalFreeFunc;

 /**
 * Especifíca o tipo da função que compara dois elementos do calendário.
 * @param a Elemento a.
 * @param b Elemento b.
 * @returns Um número positivo se a for mais antigo que b, 0 se tiverem a mesma
 *      data ou um número negativo se a for mais recente que b.
 */
typedef GCompareFunc CalCmpFunc;

 /**
 * Especifíca o tipo da função passada ao calendário para imprimir um elemento do mesmo.
 * @param e Elemento do calendário.
 */
typedef void (*CalPrintFunc)(void* e);

#endif /* __TYPES_H__ */
