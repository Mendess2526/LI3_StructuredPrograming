#include <stdlib.h>
#include <assert.h>
#include "linkList.h"

typedef struct _node{
    void* data;
    struct _node* next;
}*NODE;

struct _linkList{
    int size;
    NODE first;
    NODE last;

    LL_FreeElemFunc freeElemFunc;
};

static void nodeDestroy(LINK_LIST list, LL_FreeElemFunc freeElemFunc);
static inline void listDestroy(LINK_LIST list, LL_FreeElemFunc freeElemFunc);
static inline void addNext(NODE node, void *obj);

static inline void addNext(NODE node, void *obj){
    NODE newNode = (NODE) malloc(sizeof(struct _node));
    NODE next = node->next;
    node->next = newNode;
    newNode->next = next;
    newNode->data = obj;
}


LINK_LIST linkList_create(){
    return linkList_create_full(NULL);
}

LINK_LIST linkList_create_full(LL_FreeElemFunc freeElemFunc){
    LINK_LIST list = (LINK_LIST) malloc(sizeof(struct _linkList));
    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    list->freeElemFunc = freeElemFunc;
    return list;
}

void linkList_add(LINK_LIST list, void * obj){
    list->size++;
    NODE newNode = (NODE) malloc(sizeof(struct _node));
    newNode->data = obj;
    newNode->next = list->first;

    if(list->last == NULL)
        list->last = list->first;

    list->first = newNode;
}

void linkList_add_sorted(LINK_LIST list, void * obj, LL_SortFunc sortFunc){
    NODE cur = list->first;
    // If the list is empty or obj is smaller then head
    if(!cur || (*sortFunc)(obj, cur->data) < 0){
        linkList_add(list, obj);
    }else{
        int inserted = 0;
        while(!inserted && cur->next){
            // If obj is smaller then the next node,
            //  insert next to the current node
            if((*sortFunc)(obj, cur->next->data) < 0){
                addNext(cur, obj);
                inserted = 1;
            }else{
                cur = cur->next;
            }
        }
        // If not inserted yet, add next to current node
        if(!inserted){
            assert(cur != NULL);
            addNext(cur, obj);
        }
    }
}

void concat(LINK_LIST list1, LINK_LIST list2){
    if(!list1 || !list2) return;
    if(list1->last == NULL){
        list1->last = list2->first;
    }else{
        list1->last->next = list2->first;
    }
    listDestroy(list2, NULL);
}

static void nodeDestroy(LINK_LIST list, LL_FreeElemFunc freeElemFunc){
    NODE cur = list->first;
    while(cur){
        NODE next = cur->next;
        (*freeElemFunc)(cur->data);
        free(cur);
        cur = next;
    }
}

static inline void listDestroy(LINK_LIST list, LL_FreeElemFunc freeElemFunc){
    if(freeElemFunc){
        nodeDestroy(list, freeElemFunc);
    }
    free(list);
}

void linkList_destroy(LINK_LIST list){
    listDestroy(list, list->freeElemFunc);
}
