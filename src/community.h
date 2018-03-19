#ifndef __COMMUNITY_H__
#define __COMMUNITY_H__

#include <glib.h>

#include "pergunta.h"
#include "resposta.h"
#include "soUser.h"
#include "pair.h"

typedef GHashTable *PERGUNTAS;
typedef GHashTable *SO_USERS;

typedef struct _tcd_community *TAD_community;

TAD_community community_create();

void community_destroy(TAD_community com);

void community_add_pergunta(TAD_community com, PERGUNTA pergunta);

void community_add_resposta(TAD_community com, RESPOSTA resposta);

void community_add_user(TAD_community com, SO_USER user);

#endif /*__COMMUNITY_H__*/
