#ifndef __TYPES_H__
#define __TYPES_H__

#include <glib.h>

typedef struct TCD_community *TAD_community;


typedef struct _post *POST;


typedef struct _question *QUESTION;


typedef struct _answer *ANSWER;


typedef struct _so_user *SO_USER;


typedef struct _dateTime *DATETIME;


typedef struct _calendario *CALENDARIO;

typedef GFunc CFunc;

typedef GDestroyNotify CFreeFunc;

typedef GCompareFunc CCompareFunc;

typedef void (*CPrintFunction)(void*);

#endif /*__TYPES_H__*/