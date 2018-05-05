#ifndef __POST_H__
#define __POST_H__

/**
 * @file
 * \brief Módulo que define um post.
 */
#include "dateTime.h"
#include "question.h"
#include "answer.h"
#include "types.h"

#include <glib.h>
#include <libxml/parserInternals.h>


enum POST_TYPE{
    QUESTION_T,
    ANSWER_T
};

/**
 * Cria um post.
 * @param type O tipo do post.
 * @param c Uma questão ou resposta.
 * @returns Um post.
 */
POST post_create(enum POST_TYPE type, void* c);

/**
 * Verifica se um post é uma questão.
 * @param post Um post.
 * @returns 1 se for uma questão, 0 caso contrário.
 */
int post_is_question(POST post);

/**
 * Verifica se um post é uma resposta.
 * @param post Um post.
 * @returns 1 se for uma resposta, 0 caso contrário.
 */
int post_is_answer(POST post);

/**
 * Retorna a questão caso o post seja uma questão.
 * @param post Um post.
 * @returns A questão se o post for uma questão, caso contrário retorna NULL.
 */
QUESTION post_get_question(POST post);

/**
 * Retorna a resposta caso o post seja uma resposta.
 * @param post Um post.
 * @returns A resposta se o post for uma resposta, caso contrário retorna NULL.
 */
ANSWER post_get_answer(POST post);

/**
 * Retorna o id do post.
 * @param post Um post.
 * @returns O id do post ou - 2 caso não seja questão ou resposta.
 */
long post_get_id(POST post);

/**
 * Retorna a data do post.
 * @param post Um post.
 * @returns A data do post ou NULL caso não seja questão ou resposta.
 */
DATETIME post_get_date(POST post);

/**
 * Retorna o score do post.
 * @param post Um post.
 * @returns O score do post ou INT_MIN caso não seja questão ou resposta.
 */
int post_get_score(POST post);

/**
 * Retorna o id do autor do post.
 * @param post Um post.
 * @returns O id do autor do post ou - 2 caso não seja questão ou resposta.
 */
long post_get_owner_id(POST post);

/**
 * Retorna o nome do autor do post.
 * @param post Um post.
 * @returns O nome do autor do post ou NULL caso não seja questão ou resposta.
 */
xmlChar* post_get_owner_name(POST post);

/**
 * Liberta a memória ocupada pelo post.
 * @param post Um post.
 * @param freeQorA 1 caso se queira que seja libertada a questão/resposta do post.
 */
void post_destroy(POST post, int freeQorA);

/**
 * Liberta a memória ocupada pelo post.
 * @param post
 */
void post_destroy_generic(gpointer post);

/**
  * Se o user existir na thread a que o post pertence retorna a questão.
  * @param post Um post.
  * @param id Id do user a procurar.
  * @returns Uma questão.
  */
QUESTION post_search_thread_for_user(POST post, long id);

/**
  * Compara as datas de dois posts.
  * @param a Um post.
  * @param b Um post.
  * @returns Um número negativo se o primeiro post for mais antigo, um número
 *          positivo se o primeiro post for mais recente ou 0 se tiverem a mesma data.
  */
int post_date_cmp(gconstpointer a, gconstpointer b);

#endif /* __POST_H__ */
