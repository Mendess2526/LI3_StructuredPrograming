#ifndef __CALENDARIO_H__
#define __CALENDARIO_H__

#include "post.h"

typedef struct _calendario *CALENDARIO;


gint timeCompare(gconstpointer a, gconstpointer b);

void getId(gpointer data, gpointer user_data);

CALENDARIO calendario_create();

void calendario_add_post(CALENDARIO cal, POST post );

#endif