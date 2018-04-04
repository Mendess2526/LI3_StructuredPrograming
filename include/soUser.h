#ifndef __SO_USER_H__
#define __SO_USER_H__

#include "post.h"
#include <glib.h>

#include <libxml/parserInternals.h>

typedef struct _so_user *SO_USER;

SO_USER so_user_create(long id,
                        int reputation,
                        xmlChar *name,
                        xmlChar *bio);

long so_user_get_id(SO_USER user);

int so_user_get_reputation(SO_USER user);

xmlChar *so_user_get_name(SO_USER user);

xmlChar *so_user_get_bio(SO_USER user);

void so_user_add_post(SO_USER user, POST post);

void so_user_destroy(SO_USER user);

void so_user_destroy_generic(gpointer user);

#endif /*__SO_USER_H__*/
