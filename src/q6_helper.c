#include "q6_helper.h"
#include "community.h"
#include "dateTime.h"
#include <glib.h>

typedef struct _collector{
    int maxSize;
    ANSWERS answers;
}*COLLECTOR;

static int compareVoteCount(gpointer a, gpointer b){
    int aV = answer_get_score((ANSWER) a);
    int bV = answer_get_score((ANSWER) b);
    return aV - bV;
}

static int collect(gpointer elem, gpointer user_data){
    COLLECTOR col = (COLLECTOR) user_data;
    if(col->answers == NULL || compareVoteCount(col->answers->data, elem) < 0){
        col->answers = g_slist_prepend(col->answers, elem);
    }else{
        int i = 0;
        for(GSList* cur = col->answers; cur && i < col->maxSize; cur = cur->next, ++i){
            if(!cur->next || compareVoteCount(cur->next->data, elem) < 0){
                    cur->next = g_slist_prepend(cur->next, elem);
                    i = col->maxSize;
            }
        }
    }
    return 1;
}



LONG_list most_voted_answers_helper(TAD_community com, int N, Date begin, Date end){

    DATETIME from = dateTime_create(get_year(begin), get_month(begin), get_day(begin), 0, 0, 0, 0);
    DATETIME to = dateTime_create(get_year(end), get_month(end), get_day(end), 0, 0, 0, 0);

    COLLECTOR col = malloc(sizeof(struct _collector*));
    col->maxSize = N;
    col->answers = NULL;

    community_iterate_answers(com ,from, to, col, collect);

    LONG_list l = create_list(N);
    ANSWERS cur = col->answers;
    for(int i=0; cur && i<N; cur = cur->next, i++)
        set_list(l, i, answer_get_id(cur->data));

    dateTime_destroy(from);
    dateTime_destroy(to);
    g_slist_free(col->answers);
    free(col);

    return l;
}
