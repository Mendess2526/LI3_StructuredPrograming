#ifndef __POST_H__
#define __POST_H__

#include "date.h"
#include <glib.h>

#include <libxml/parserInternals.h>

typedef struct _post *POST;

long post_get_id(POST post);

Date post_get_date(POST post);

int post_get_score(POST post);

long post_get_owner_id(POST post);

int post_get_comment_count(POST post);

int post_get_type(POST post);

xmlChar *post_get_owner_display_name(POST post);

#endif /*__POST_H__*/
