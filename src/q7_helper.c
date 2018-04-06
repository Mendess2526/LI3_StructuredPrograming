#include "q7_helper.h"
#include "community.h"
#include "list.h"

#include <glib.h>

typedef struct collector{
    int maxSize;
    GSList* list;
}*COLLECTOR;

void collect(COLLECTOR col, gpointer elem, CCompareFunc cmpFunc){
    if(col->list == NULL || (*cmpFunc)(col->list->data, elem) < 0)
        col->list = g_slist_prepend(col->list, elem);
    else{
        int i = 0;
        for(GSList* cur = col->list; cur && i < col->maxSize; cur = cur->next, ++i){
            if(!cur->next || (*cmpFunc)(cur->next->data, elem) < 0){
                    cur->next = g_slist_prepend(cur->next, elem);
                    i = col->maxSize;
            }
        }
    }
}

int compareScore(gconstpointer a, gconstpointer b){
    int aC = question_get_answer_count((QUESTION) a);
    int bC = question_get_answer_count((QUESTION) b);
    return aC - bC;
}

void collectFunc(gpointer elem, gpointer user_data){
    collect((COLLECTOR) user_data, (QUESTION) elem, compareScore);
}

LONG_list gslist2llist(GSList* list, int maxSize){
    LONG_list l = create_list(maxSize);
    int i = 0;
    for(; list && i<maxSize; list = list->next){
        set_list(l, i++, question_get_id(list->data));
    }
    return l;
}

LONG_list most_answered_questions_helper(TAD_community com,
                                        int maxSize,
                                        Date begin,
                                        Date end){

    COLLECTOR col = (COLLECTOR) malloc(sizeof(struct collector));
    col->list = NULL;
    col->maxSize = maxSize;

    community_iterate_questions(com, begin, end, col, collectFunc);

    LONG_list r = gslist2llist(col->list, maxSize);

    g_slist_free(col->list);
    g_free(col);

    return r;
}
