#ifndef __COMMUNITY_H__
#define __COMMUNITY_H__

#include <glib.h>

#include "soUser.h"
#include "post.h"

typedef GHashTable *QUESTIONS;
typedef GHashTable *ANSWERS;
typedef GHashTable *SO_USERS;

typedef struct _tcd_community *TAD_community;

TAD_community init();

TAD_community community_create();

void community_destroy(TAD_community com);

void community_add_post(TAD_community com, POST post);

void community_add_user(TAD_community com, SO_USER user);

void community_add_favorite(TAD_community com, long id);

#endif /*__COMMUNITY_H__*/
