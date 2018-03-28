#ifndef __POST_H__
#define __POST_H__

#include "dateTime.h"
#include "question.h"
#include "answer.h"
#include <glib.h>

#include <libxml/parserInternals.h>

typedef struct _post *POST;

enum POST_TYPE{
    QUESTION_T,
    ANSWER_T
};

POST post_create(enum POST_TYPE type, void *c);

int post_is_question(POST post);

int post_is_answer(POST post);

QUESTION post_get_question(POST post);

ANSWER post_get_answer(POST post);

long post_get_id(POST post);

DATETIME post_get_date(POST post);

int post_get_score(POST post);

long post_get_owner_id(POST post);

xmlChar *post_get_owner_name(POST post);

void post_destroy(POST post);

void post_destroy_generic(gpointer post);

#endif /*__POST_H__*/
