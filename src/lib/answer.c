#include "answer.h"
#include <stdlib.h>

struct _answer{
    int score;
    int comment_count;
    long id;
    long parent_id;
    long owner_id;
    DATETIME date;
    QUESTION parent_ptr;
    xmlChar *owner_name;
};

ANSWER answer_create(long id, DATETIME date, int score, long ownerId, long parentId, xmlChar *ownerName, int comment_count){
    ANSWER answer = (ANSWER) malloc(sizeof(struct _answer));
    answer->id = id;
    answer->date = date;
    answer->score = score;
    answer->comment_count = comment_count;
    answer->owner_id = ownerId;
    answer->parent_id = parentId;
    answer->parent_ptr = NULL;
    answer->owner_name = xmlStrdup(ownerName);
    return answer;
}

long answer_get_id(ANSWER answer){
    return answer->id;
}

DATETIME answer_get_date(ANSWER answer){
    return answer->date;
}

int answer_get_score(ANSWER answer){
    return answer->score;
}

long answer_get_owner_id(ANSWER answer){
    return answer->owner_id;
}

int answer_get_comment_count(ANSWER answer){
    return answer->comment_count;
}

xmlChar *answer_get_owner_name(ANSWER answer){
    return answer->owner_name;
}

long answer_get_parent_id(ANSWER answer){
    return answer->parent_id;
}

QUESTION answer_get_parent_ptr(ANSWER answer){
    return answer->parent_ptr;
}

void answer_set_parent_ptr(ANSWER answer, QUESTION question){
    answer->parent_ptr = question;
}

void answer_destroy(ANSWER answer){
    dateTime_destroy (answer->date);
    xmlFree(answer->owner_name);
    free(answer);
}

void answer_destroy_generic(gpointer answer){
    answer_destroy((ANSWER) answer);
}

int answer_date_cmp(const void* a, const void* b){
    DATETIME dataA = answer_get_date((ANSWER) b);
    DATETIME dataB = answer_get_date((ANSWER) a);
    return dateTime_compare(dataA, dataB);
}

int answer_score_cmp(const void* a, const void* b){
    return answer_get_score((ANSWER) a)
         - answer_get_score((ANSWER) b);
}
