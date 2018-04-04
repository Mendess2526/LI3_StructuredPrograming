#include "question.h"
#include <stdlib.h>

typedef GSList * ANSWERS;

struct _question{
    int score;
    int answer_count;
    long id;
    long owner_id;
    DATETIME date;
    xmlChar *ownerName;
    xmlChar *title;
    xmlChar *tags;
    ANSWERS answers;
};

QUESTION question_create(long id, DATETIME date, int score, long ownerId,
                        xmlChar *title, xmlChar *tags, int answerCount, xmlChar *ownerName){
    QUESTION q = malloc(sizeof(struct _question));
    q->id = id;
    q->date = date;
    q->score = score;
    q->owner_id = ownerId;
    q->title = xmlStrdup(title);
    q->tags = xmlStrdup(tags);
    q->answer_count = answerCount;
    q->ownerName = xmlStrdup(ownerName);
    q->answers = NULL;
    return q;
}

long question_get_id(QUESTION question){
    return question->id;
}

DATETIME question_get_date(QUESTION question){
    return question->date;
}

int question_get_score(QUESTION question){
    return question->score;
}

long question_get_owner_id(QUESTION question){
    return question->owner_id;
}

xmlChar *question_get_title(QUESTION question){
    return xmlStrdup(question->title);
}

xmlChar **question_get_tags(QUESTION question){
    return NULL;
}

xmlChar *question_get_owner_name(QUESTION question){
    return xmlStrdup(question->ownerName);
}

int question_get_answer_count(QUESTION question){
    return question->answer_count;
}

ANSWERS question_get_answers(QUESTION question){
    return question->answers;
}

void question_destroy(QUESTION question){
    dateTime_destroy (question->date);
    xmlFree(question->title);
    xmlFree(question->tags);
    xmlFree(question->ownerName);
    g_slist_free_full(question->answers, answer_destroy_generic);
    free(question);
}

void question_destroy_generic(gpointer question){
    question_destroy((QUESTION) question);
}

void question_add_answer(QUESTION question, ANSWER answer){
    question->answers = g_slist_prepend(question->answers, answer);
}