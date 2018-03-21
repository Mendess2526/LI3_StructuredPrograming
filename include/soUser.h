#ifndef __SO_USER_H__
#define __SO_USER_H__

#include "post.h"
#include <glib.h>
typedef struct _so_user *SO_USER;

SO_USER so_user_create(long id,
                        int reputation,
                        char *name,
                        char *bio);

SO_USER so_user_create_empty(long id);

long so_user_get_id(SO_USER user);

int so_user_get_reputation(SO_USER user);

char *so_user_get_name(SO_USER user);

char *so_user_get_bio(SO_USER user);

void so_user_add_post(SO_USER user, POST post);

void so_user_destroy(SO_USER user);

void so_user_destroy_generic(gpointer user);
//should free memory
SO_USER so_user_merge(SO_USER oldU, SO_USER newU);

#endif /*__SO_USER_H__*/
