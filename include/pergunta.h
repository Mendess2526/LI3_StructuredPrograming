#ifndef __PERGUNTA_H__
#define __PERGUNTA_H__

#include "date.h"

typedef struct _pergunta *PERGUNTA;

PERGUNTA create_pergunta(int id,
                        Date date,
                        int score,
                        int ownerId,
                        char *title,
                        char *tags,
                        int answerCount,
                        char *ownerName);

int get_id(PERGUNTA pergunta);

void destroy_pergunta(PERGUNTA pergunta);

#endif /*__PERGUNTA_H__*/