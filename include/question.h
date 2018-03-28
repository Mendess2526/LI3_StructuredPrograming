#ifndef __QUESTION_H__
#define __QUESTION_H__

#include "dateTime.h"
#include "answer.h"
#include <glib.h>

#include <libxml/parserInternals.h>

typedef struct _question *QUESTION;

QUESTION question_create(long id,
                        DATETIME date,
                        int score,
                        long ownerId,
                        xmlChar *title,
                        xmlChar *tags,
                        int answerCount,
                        xmlChar *ownerName);

QUESTION question_create_empty(long id);

long question_get_id(QUESTION question);

DATETIME question_get_date(QUESTION question);

int question_get_score(QUESTION question);

long question_get_owner_id(QUESTION question);

xmlChar *question_get_title(QUESTION question);

xmlChar **question_get_tags(QUESTION question);

xmlChar *question_get_owner_name(QUESTION question);

int question_get_answer_count(QUESTION question);

void question_destroy(QUESTION question);

void question_destroy_generic(gpointer question);

void question_add_answer(QUESTION question, ANSWER answer);
//should free newP
QUESTION question_merge(QUESTION oldQ, QUESTION newQ);

#endif /*__QUESTION_H__*/
