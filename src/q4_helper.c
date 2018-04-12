#include "q4_helper.h"
#include <glib.h>
#include <string.h>
#include "question.h"
#include "dateTime.h"
#include "community.h"

typedef struct _darray{
    int size;
    int load;
    long* array;
}*DArray;

typedef struct _collector{
    char* tag;
    DArray questionIds;
}*COLLECTOR;

DArray darray_create(int size){
    if(size < 1) size = 100;
    DArray a = malloc(sizeof(struct _darray));
    a->load = 0;
    a->size = 30;
    a->array = malloc(sizeof(long)*size);
    return a;
}

void darray_append(DArray a, long val){
    if(a->load >= a->size){
        a->size *=2;
        a->array = realloc(a->array, sizeof(long)*a->size);
    }
    a->array[a->load++] = val;
}

void darray_destroy(DArray a){
    free(a->array);
    free(a);
}

int contains(char** strings, char* string){
    while(*strings){
        if(!strcmp(*strings,string)) return 1;
        strings++;
    }
    return 0;
}

int collect(gpointer elem, gpointer user_data){
    QUESTION q = (QUESTION) elem;
    COLLECTOR col = (COLLECTOR) user_data;
    if(contains(question_get_tags(q), col->tag))
        darray_append(col->questionIds, question_get_id(q));

    return 1;
}

LONG_list questions_with_tag_helper(TAD_community com, char* tag, Date begin, Date end){
    DATETIME from = dateTime_create(get_year(end), get_month(end), get_day(end), 23, 59, 59, 999);
    DATETIME to = dateTime_create(get_year(begin), get_month(begin), get_day(begin), 0, 0, 0, 0);

    COLLECTOR col = malloc(sizeof(struct _collector));
    col->tag = tag;
    col->questionIds = darray_create(10000);

    community_iterate_questions(com, from, to, col, collect);

    int length = col->questionIds->load;
    LONG_list l = create_list(length);
    for(int i=0; i<length; i++) set_list(l, i, 0);
    for(int i=0; i<length; i++)
        set_list(l, i, col->questionIds->array[i]);


    dateTime_destroy(from);
    dateTime_destroy(to);
    darray_destroy(col->questionIds);
    free(col);
    return l;
}
