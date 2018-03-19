#ifndef __RESPOSTA_H__
#define __RESPOSTA_H__

#include "date.h"

typedef struct _resposta *RESPOSTA;

RESPOSTA resposta_create(long id,
                        Date date,
                        int score,
                        long ownerId,
                        long parentId,
                        char *ownerName);

long resposta_get_id(RESPOSTA resposta);

Date resposta_get_date(RESPOSTA resposta);

int resposta_get_score(RESPOSTA resposta);

long resposta_get_owner_id(RESPOSTA resposta);

int resposta_get_comment_count(RESPOSTA resposta);

char *resposta_get_owner_name(RESPOSTA resposta);

long resposta_get_parent_id(RESPOSTA resposta);

void resposta_destroy(RESPOSTA resposta);

#endif /*__RESPOSTA_H__*/
