#ifndef __POST_H__
#define __POST_H__

#include "dateTime.h"
#include "question.h"
#include "answer.h"
#include <glib.h>
#include "types.h"

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
 * @returns 1 se for uma questão 0 caso contrário.
 */
int post_is_question(POST post);

 /**
 * Verifica se um post é uma resposta.
 * @param post Um post.
 * @returns 1 se for uma resposta 0 caso contrário.
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
 * Retorna o id do dono do post.
 * @param post Um post.
 * @returns O id do dono do post ou - 2 caso não seja questão ou resposta.
 */
long post_get_owner_id(POST post);

 /**
 * Retorna o nome do dono do post.
 * @param post Um post.
 * @returns O nome do dono do post ou NULL caso não seja questão ou resposta.
 */
xmlChar *post_get_owner_name(POST post);

 /**
 * Liberta a memória ocupada pelo post.
 * @param post Um post.
 * @param freeQorA 1 caso se queira que seja libertada a questão/resposta do post.
 */
void post_destroy(POST post, int freeQorA);

 /**
 *
 * @param post
 */
void post_destroy_generic(gpointer post);

int post_date_cmp(gconstpointer a, gconstpointer b);

long post_search_thread_for_user(POST post, long id);

#endif /*__POST_H__*/
