#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "dateTime.h"
#include "question.h"
#include <glib.h>

#include <libxml/parserInternals.h>

typedef struct _answer *ANSWER;

/**
 *Cria uma resposta. 
 * @param id O id da resposta. 
 * @param date A data da resposta.
 * @param score O score da resposta.
 * @param ownerId O id do dono da resposta.
 * @param parentId O id da questão à qual foi dada a resposta.
 * @param ownerName O nome do dono da resposta.
 * @returns Uma resposta. 
 */
ANSWER answer_create(long id,
                        DATETIME date,
                        int score,
                        long ownerId,
                        long parentId,
                        xmlChar *ownerName,
                        int comment_count);

long answer_get_id(ANSWER answer);

DATETIME answer_get_date(ANSWER answer);

int answer_get_score(ANSWER answer);

long answer_get_owner_id(ANSWER answer);

int answer_get_comment_count(ANSWER answer);

xmlChar *answer_get_owner_name(ANSWER answer);

long answer_get_parent_id(ANSWER answer);

QUESTION answer_get_parent_ptr(ANSWER answer);

void answer_set_parent_ptr(ANSWER answer, QUESTION question);

void answer_destroy(ANSWER answer);

void answer_destroy_generic(gpointer answer);

#endif /*__ANSWER_H__*/
