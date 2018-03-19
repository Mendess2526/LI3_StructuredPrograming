#ifndef __RESPOSTA_H__
#define __RESPOSTA_H__

#include "date.h"

typedef struct _resposta *RESPOSTA;

RESPOSTA create_resposta(int id,
                        Date date,
                        int score,
                        int ownerId,
                        char *ownerName);

void destroy_resposta(RESPOSTA resposta);

#endif /*__RESPOSTA_H__*/