#ifndef __QUESTION_H__
#define __QUESTION_H__

#include "date.h"
#include "answer.h"

typedef struct _question *QUESTION;

QUESTION question_create(long id,
                        Date date,
                        int score,
                        long ownerId,
                        char *title,
                        char *tags,
                        int answerCount,
                        char *ownerName);

QUESTION question_create_empty(long id);

long question_get_id(QUESTION question);

Date question_get_date(QUESTION question);

int question_get_score(QUESTION question);

long question_get_owner_id(QUESTION question);

char *question_get_title(QUESTION question);

char **question_get_tags(QUESTION question);

int question_get_answer_count(QUESTION question);

int question_get_favorite_count(QUESTION question);

void question_destroy(gpointer question);

void question_add_answer(QUESTION question, ANSWER answer);
//should free memory
QUESTION question_merge(QUESTION oldP, QUESTION newP);

#endif /*__QUESTION_H__*/
