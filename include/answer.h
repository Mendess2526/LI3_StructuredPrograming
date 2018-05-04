#ifndef __ANSWER_H__
#define __ANSWER_H__

/**
 * @file
 * \brief Módulo que define uma resposta.
 */
#include "dateTime.h"
#include "question.h"
#include "types.h"

#include <glib.h>
#include <libxml/parserInternals.h>

/**
 * Cria uma resposta.
 * @param id O id da resposta.
 * @param date A data da resposta.
 * @param score O score da resposta.
 * @param ownerId O id do autor da resposta.
 * @param parentId O id da questão à qual foi dada a resposta.
 * @param ownerName O nome do autor da resposta.
 * @param comment_count O número de comentários da resposta.
 * @returns Uma resposta.
 */
ANSWER answer_create(long id,
                    DATETIME date,
                    int score,
                    long ownerId,
                    long parentId,
                    const xmlChar *ownerName,
                    int comment_count);

/**
 * Retorna o id da resposta.
 * @param answer Uma resposta.
 * @returns O id da resposta.
 */
long answer_get_id(ANSWER answer);

/**
 * Retorna a data da resposta.
 * @param answer Uma resposta.
 * @returns A data da resposta.
 */
DATETIME answer_get_date(ANSWER answer);

/**
 * Retorna o score da resposta.
 * @param answer Uma resposta.
 * @returns A data da resposta.
 */
int answer_get_score(ANSWER answer);

/**
 * Retorna o id do autor da resposta.
 * @param answer Uma resposta.
 * @returns O autor da resposta.
 */
long answer_get_owner_id(ANSWER answer);

/**
 * Retorna o número de comentários da resposta.
 * @param answer Uma resposta.
 * @returns O número de comentários da resposta.
 */
int answer_get_comment_count(ANSWER answer);

/**
 * Retorna o nome do autor da resposta.
 * @param answer Uma resposta.
 * @returns A nome do autor da resposta.
 */
xmlChar *answer_get_owner_name(ANSWER answer);

/**
 * Retorna o id da questão à qual foi dada a resposta.
 * @param answer Uma resposta.
 * @returns A data da resposta.
 */
long answer_get_parent_id(ANSWER answer);

/**
 * Retorna a questão à qual foi dada a resposta.
 * @param answer Uma resposta.
 * @returns A questão à qual foi dada a resposta.
 */
QUESTION answer_get_parent_ptr(ANSWER answer);

/**
 * Inicializa o apontador para a questão à qual foi dada a resposta.
 * @param answer Uma resposta.
 * @param question A questão que está a ser respondida.
 */
void answer_set_parent_ptr(ANSWER answer, QUESTION question);

/**
 * Liberta a memória ocupada pela resposta.
 * @param answer Uma resposta.
 */
void answer_destroy(ANSWER answer);

/**
 * Liberta a memória ocupada pela resposta.
 * @param answer Uma resposta.
 */
void answer_destroy_generic(gpointer answer);

/**
 * Compara duas respostas conforme a data.
 * @param a Uma resposta.
 * @param b Uma resposta.
 * @returns Um número negativo se a primeira resposta for mais antiga, um número
 *          positivo se a primeira resposta for mais recente ou 0 se as respostas
 *          tiverem a mesma data.
 */
int answer_date_cmp(const void* a, const void* b);

/**
 * Compara duas respostas conforme o score.
 * @param a Uma resposta.
 * @param b Uma resposta.
 * @returns Um número positivo se a resposta a tem um score superior, um número
 *          negativo se a resposta b tem um score superior ou 0 se têm score
 *          igual.
 */
int answer_score_cmp(const void* a, const void* b);

#endif /* __ANSWER_H__ */