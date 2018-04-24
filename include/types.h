#ifndef __TYPES_H__
#define __TYPES_H__
/**
 * @file
 * Modulo que define os princípais tipos usados.
 */
#include <glib.h>

 /** Tipo abstrato de dados. */
typedef struct TCD_community * TAD_community;

 /**
 * Especifíca o tipo de função passada à TAD_community para comparar elementos desta.
 * @param a Elemento a.
 * @param b Elemento b.
 * @returns Positivo se a for maior que b, 0 se forem iguais, negativo se b menor que a.
 */
typedef int (*ComCmpFunc)(const void* a, const void* b);

 /** Tipo abstrato de post. */
typedef struct _post * POST;

 /** Tipo abstrato de questão. */
typedef struct _question * QUESTION;

 /** Lista ligada de respostas. */
typedef GSList * ANSWERS;

 /** Tipo abstrato de resposta. */
typedef struct _answer * ANSWER;

 /** Tipo abstrato de user. */
typedef struct _so_user * SO_USER;

 /** Tipo abstrato de DateTime. */
typedef struct _dateTime * DATETIME;

 /** Tipo abstrato de Calendário. */
typedef struct _calendario * CALENDARIO;

 /**
 * Especifíca o tipo de função passada ao calendário para operar sobre os elementos do mesmo.
 * @param elem Elemento do calendário.
 * @param user_data Informação do utilizador.
 * @returns 0 se a iteração sobre os elementos deve terminar, 1 caso contrário.
 */
typedef int (*CFunc)(void* elem, void* user_data);

 /** Especifíca o tipo da função chamada para cada elemento do calendário para libertar a memória ocupada por este.
 *  @param data Elemento a destruir.
 */
typedef GDestroyNotify CFreeFunc;
 /**
 * Especifíca o tipo da função que compara dois elementos do calendário.
 * @param a Elemento a.
 * @param b Elemento b.
 * @returns Positivo se a for mais antigo que b, 0 se tiverem a mesma data,
 *          negativo se a for mais recente que b.
 */
typedef GCompareFunc CCompareFunc;

 /**
 * Especifíca o tipo da função passada ao calendário para imprimir um elemento do mesmo.
 * @param e Elemento do calendário.
 */
typedef void (*CPrintFunction)(void* e);

#endif /* __TYPES_H__ */
