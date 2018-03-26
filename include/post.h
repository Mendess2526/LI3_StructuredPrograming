#ifndef __POST_H__
#define __POST_H__

#include "date.h"
#include "question.h"
#include "answer.h"
#include <glib.h>

#include <libxml/parserInternals.h>

typedef struct _post *POST;

int isQuestion(POST post);

int isAnswer(POST post);

QUESTION post_get_question(POST post);

ANSWER post_get_answer(POST post);

#endif /*__POST_H__*/
