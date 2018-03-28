#ifndef __CALENDARIO_H__
#define __CALENDARIO_H__

#include "post.h"
#include "date.h"

typedef struct _calendario *CALENDARIO;


CALENDARIO calendario_create();

void calendario_add_post(CALENDARIO cal, POST post );

long *calendario_get_ids(CALENDARIO cal, Date from, Date to);

void calendario_destroy(CALENDARIO cal);
#endif
