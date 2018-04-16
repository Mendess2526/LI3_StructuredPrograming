#include "q8_helper.h"
#include "community.h"
#include <string.h>

typedef struct collector{
    int maxSize;
    int index;
    char* word;
    LONG_list list;
}*COLLECTOR;

static int collect(gpointer elem, gpointer user_data){
    COLLECTOR col = (COLLECTOR) user_data;
    if(col->index >= col->maxSize) return 0;

    QUESTION q = (QUESTION) elem;
    if(col->index < col->maxSize &&
            strstr((char*) question_get_title(q), col->word)){
        set_list(col->list, col->index++, question_get_id(q));
    }
    return 1;
}

LONG_list contains_word_helper(TAD_community com, char* word, int N){
    COLLECTOR col = malloc(sizeof(struct collector));
    col->maxSize = N;
    col->index = 0;
    col->word = word;
    col->list = create_list(N);
    for(int i=0; i<N; i++) set_list(col->list, i, 0);

    DATETIME from = dateTime_get_epoch();
    DATETIME to = dateTime_get_year2038();

    community_iterate_questions(com, from, to, col, collect);

    dateTime_destroy(from);
    dateTime_destroy(to);

    LONG_list list = col->list;
    free(col);
    return list;
}
