#ifndef __COMMUNITY_H__
#define __COMMUNITY_H__

#include <glib.h>
#include "date.h"
#include "soUser.h"
#include "answer.h"
#include "question.h"

typedef GHashTable *QUESTIONS;
typedef GHashTable *ANSWERS;
typedef GHashTable *SO_USERS;

typedef struct TCD_community *TAD_community;

TAD_community init();

TAD_community community_create();

void community_destroy(TAD_community com);

void community_add_question(TAD_community com, QUESTION question);

void community_add_answer(TAD_community com, ANSWER answer);

void community_add_user(TAD_community com, SO_USER user);

void community_add_favorite(TAD_community com, long id);

SO_USER community_get_user(TAD_community com, long id);

QUESTION community_get_question(TAD_community com, long id);

ANSWER community_get_answer(TAD_community com, long id);

void community_get_question_ids(TAD_community com, Date from, Date to, void *user_data, GFunc calFunc);

void community_get_answer_ids(TAD_community com, Date from, Date to, void *user_data, GFunc calFunc);

/* ------------- PRINTING --------------------- */


void printUsers(TAD_community com);

void printQuestions(TAD_community com);

void printAnswers(TAD_community com);

void printFavouritesCount(TAD_community com);

void community_print_calendario(TAD_community com);

#endif /*__COMMUNITY_H__*/
