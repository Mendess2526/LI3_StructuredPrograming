#ifndef __QUESTION_H__
#define __QUESTION_H__

#include "dateTime.h"
#include "answer.h"
#include <glib.h>

#include <libxml/parserInternals.h>

typedef struct _question *QUESTION;

/**
 * Cria uma questão.
 * @param id O id da questão.
 * @param date A data da questão.
 * @param score O score da questão.
 * @param ownerId O id do dono da questão.
 * @param title O título da questão.
 * @param tags As tags da questão.
 * @param answerCount Conta o número de respostas que a questão tem.
 * @param ownerName O nome do dono da questão.
 * @returns Uma questão.
 */
QUESTION question_create(long id,
                        DATETIME date,
                        int score,
                        long ownerId,
                        xmlChar *title,
                        xmlChar *tags,
                        int answerCount,
                        xmlChar *ownerName);

/**
 * Retorna o id da questão.
 * @param question Uma questão.
 * @returns O id da questão.
 */
long question_get_id(QUESTION question);

/**
 * Retorna a data da questão.
 * @param question Uma questão.
 * @returns A data da questão.
 */
DATETIME question_get_date(QUESTION question);

/**
 * Retorna o score da questão.
 * @param question Uma questão.
 * @returns O score da questão.
 */
int question_get_score(QUESTION question);

/**
 * Retorna o id do dono da questão.
 * @param question Uma questão.
 * @returns O id do dono da questão.
 */
long question_get_owner_id(QUESTION question);

/**
 * Retorna o título da questão.
 * @param question Uma questão.
 * @returns O título da questão.
 */
xmlChar *question_get_title(QUESTION question);

/**
 * Retorna as tags da questão.
 * @param question Uma questão.
 * @returns As tags da questão.
 */
char** question_get_tags(QUESTION question);

/**
 * Retorna o nome do dono da questão.
 * @param question Uma questão.
 * @returns O nome do dono da questão.
 */
xmlChar *question_get_owner_name(QUESTION question);

/**
 * Retorna o número de resposta que a questão tem.
 * @param question Uma questão.
 * @returns O número de respostas que a questão tem.
 */
int question_get_answer_count(QUESTION question);

/**
 * \brief Adiciona uma resposta na lista de respostas da questão.
 * Inicializa também o apontador para esta questão na resposta
 * passada
 * @param question Uma questão.
 * @param answer Uma resposta.
 */
void question_add_answer(QUESTION question, ANSWER answer);

/**
 * Liberta a memória ocupada pela questão.
 * @param question Uma questão.
 */
void question_destroy(QUESTION question);

/**
 * 
 * @param question
 */
void question_destroy_generic(gpointer question);

#endif /*__QUESTION_H__*/
