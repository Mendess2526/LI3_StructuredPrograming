#include "q7_helper.h"
#include "community.h"
#include "list.h"

#include <glib.h>

typedef struct collector{
    int N;
    GSList* list;
}*COLLECTOR;

int compareScore(gconstpointer a, gconstpointer b){
    int aS = question_get_score((QUESTION) a);
    int bS = question_get_score((QUESTION) b);
    return (aS > bS) - (aS < bS);
}


void collectFunc(gpointer user_data, gpointer elem){
    COLLECTOR col = (COLLECTOR) user_data;
    QUESTION q = (QUESTION) elem;
    col->list = g_slist_insert_sorted(col->list,q,compareScore);
}

LONG_list gslist2llist(GSList* list, int N){
    LONG_list l = create_list(N);
    int i = 0;
    for(QUESTION question = list->data; list && i<N; list = list->next){
        set_list(l, i++, question_get_id(question));
    }
    return l;
}

LONG_list most_answered_questions_helper(TAD_community com,
                                        int N,
                                        Date begin,
                                        Date end){

    COLLECTOR col = (COLLECTOR) malloc(sizeof(struct collector));
    col->list = NULL;
    col->N = N;

    community_iterate_questions(com, begin, end, col, collectFunc);

    return gslist2llist(col->list, N);
}
