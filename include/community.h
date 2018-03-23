#ifndef __COMMUNITY_H__
#define __COMMUNITY_H__

#include <glib.h>

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

#endif /*__COMMUNITY_H__*/
