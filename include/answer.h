#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "date.h"

typedef struct _answer *ANSWER;

ANSWER answer_create(long id,
                        Date date,
                        int score,
                        long ownerId,
                        long parentId,
                        char *ownerName);

long answer_get_id(ANSWER answer);

Date answer_get_date(ANSWER answer);

int answer_get_score(ANSWER answer);

long answer_get_owner_id(ANSWER answer);

int answer_get_comment_count(ANSWER answer);

char *answer_get_owner_name(ANSWER answer);

int answer_get_favorite_count(ANSWER answer);

long answer_get_parent_id(ANSWER answer);

void answer_destroy(ANSWER answer);

void answer_destroy_generic(gpointer answer);

void answer_add_favorite(ANSWER answer);

#endif /*__ANSWER_H__*/
