#ifndef __COMMUNITY_H__
#define __COMMUNITY_H__

#include <glib.h>

#include "question.h"
#include "answer.h"
#include "soUser.h"
#include "pair.h"

typedef GHashTable *QUESTIONS;
typedef GHashTable *SO_USERS;

typedef struct _tcd_community *TAD_community;

TAD_community community_create();

void community_destroy(TAD_community com);

void community_add_question(TAD_community com, QUESTION question);

void community_add_answer(TAD_community com, ANSWER answer);

void community_add_user(TAD_community com, SO_USER user);

#endif /*__COMMUNITY_H__*/
