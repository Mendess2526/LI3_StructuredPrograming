#include "answer.h"

struct _answer{
    int parent_id;
    int favorite_count;
    int score;
    int comment_count;
    long id;
    long owner_id;
    Date date;
    xmlChar *owner_name;
};

ANSWER answer_create(long id, Date date, int score, long ownerId, long parentId, xmlChar *ownerName, int comment_count){
    ANSWER answer = malloc(sizeof(struct _answer)); 
    answer->id = id;
    answer->date = date;
    answer->score = score;
    answer->comment_count = comment_count;
    answer->owner_id = ownerId;
    answer->parent_id = parentId;
    answer->owner_name = xmlStrdup(ownerName);
    return answer;
}

long answer_get_id(ANSWER answer){
    return answer->id;
}

Date answer_get_date(ANSWER answer){
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
    return xmlStrdup(answer->owner_name);
}

int answer_get_favorite_count(ANSWER answer){
    return answer->favorite_count;
}

long answer_get_parent_id(ANSWER answer){
    return answer->parent_id;
}

void answer_destroy(ANSWER answer){
    free(answer);
}

//falta
void answer_destroy_generic(gpointer answer){
    answer_destroy((ANSWER) answer);
}

void answer_add_favorite(ANSWER answer){
    answer->favorite_count+=1;
}