#ifndef __CALENDARIO_H__
#define __CALENDARIO_H__

#include "post.h"
#include "date.h"

typedef struct _calendario *CALENDARIO;


gint timeCompare(gconstpointer a, gconstpointer b);

void getId(gpointer data, gpointer user_data);

CALENDARIO calendario_create();

void calendario_add_post(CALENDARIO cal, POST post );

long *calendario_get_ids(CALENDARIO cal, Date from, Date to);

#endif
