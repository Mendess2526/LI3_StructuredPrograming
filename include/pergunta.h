#ifndef __PERGUNTA_H__
#define __PERGUNTA_H__

#include "date.h"
#include "resposta.h"

typedef struct _pergunta *PERGUNTA;

PERGUNTA pergunta_create(long id,
                        Date date,
                        int score,
                        long ownerId,
                        char *title,
                        char *tags,
                        int answerCount,
                        char *ownerName);

PERGUNTA pergunta_create_empty(long id);

long pergunta_get_id(PERGUNTA pergunta);

Date pergunta_get_date(PERGUNTA pergunta);

int pergunta_get_score(PERGUNTA pergunta);

long pergunta_get_owner_id(PERGUNTA pergunta);

char *pergunta_get_title(PERGUNTA pergunta);

char **pergunta_get_tags(PERGUNTA pergunta);

int pergunta_get_answer_count(PERGUNTA pergunta);

void pergunta_destroy(gpointer pergunta);

void pergunta_add_resposta(PERGUNTA pergunta, RESPOSTA resposta);
//should free memory
PERGUNTA pergunta_merge(PERGUNTA oldP, PERGUNTA newP);

#endif /*__PERGUNTA_H__*/
