#ifndef __TYPES_H__
#define __TYPES_H__

#include <glib.h>

 /**
 * .
 * .
 */
typedef struct TCD_community * TAD_community;

typedef int (*ComCmpFunc)(void* a, void* b);

 /**
 * .
 * .
 */
typedef struct _post * POST;

 /**
 * .
 * .
 */
typedef struct _question * QUESTION;

 /**
 * .
 * .
 */
typedef GSList * ANSWERS;

 /**
 * .
 * .
 */
typedef struct _answer * ANSWER;

 /**
 * .
 * .
 */
typedef struct _so_user * SO_USER;

 /**
 * .
 * .
 */
typedef struct _dateTime * DATETIME;

 /**
 * .
 * .
 */
typedef struct _calendario * CALENDARIO;

 /**
 * .
 * .
 */
typedef int (*CFunc)(void* elem, void* user_data);

 /**
 * .
 * .
 */
typedef GDestroyNotify CFreeFunc;
 /**
 * .
 * .
 */
typedef GCompareFunc CCompareFunc;
 /**
 * .
 * .
 */
typedef void (*CPrintFunction)(void*);

#endif /*__TYPES_H__*/
