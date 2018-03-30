#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

typedef struct _linkList * LINK_LIST;

typedef int (*LL_SortFunc)(void *a,void*b);

typedef void (*LL_FreeElemFunc)(void *data);

LINK_LIST linkList_create();

LINK_LIST linkList_create_full(LL_FreeElemFunc freeElemFunc);

void linkList_add(LINK_LIST list, void * obj);

void linkList_add_sorted(LINK_LIST list, void * obj, LL_SortFunc sortFunc);

void concat(LINK_LIST list1, LINK_LIST list2);

void linkList_destroy(LINK_LIST list);

#endif /*__LINK_LIST_H__*/
