#ifndef __CALENDARIO_H__
#define __CALENDARIO_H__

#include "post.h"
#include "date.h"

#include <glib.h>

typedef struct _calendario *CALENDARIO;

typedef GFunc CFunc;

typedef GDestroyNotify CFreeFunc;

typedef GCompareFunc CCompareFunc;

CALENDARIO calendario_create(int nAnos, CCompareFunc compareFunc, CFreeFunc freeFunc);

void calendario_add_post(CALENDARIO cal, void* post, DATETIME d);

void calendario_get_ids(CALENDARIO cal, Date from, Date to, void *user_data, CFunc calFunc);

void calendario_destroy(CALENDARIO cal);

void printCalendario(CALENDARIO cal);

#endif
