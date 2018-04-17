#include "question.h"
#include "common.h"

#include <stdlib.h>
#include <string.h>

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
    return question->title;
}

char** question_get_tags(QUESTION question){
    if(!question->tags || question->tags == '\0') return NULL;
    xmlChar* tagsUnparsed = xmlStrdup(question->tags);
    char** result = malloc(sizeof(char *)*6);
    memset(result, 0, sizeof(char*)*6);
    char* token = strtok((char *) tagsUnparsed+1, "><");
    int i = 0;
    while (token != NULL) {
        result[i++] = mystrdup(token);
        token = strtok(NULL, "><");
    }
    free(tagsUnparsed);
    return result;
}

xmlChar *question_get_owner_name(QUESTION question){
    return question->ownerName;
}

int question_get_answer_count(QUESTION question){
    return question->answer_count;
}

ANSWERS question_get_answers(QUESTION question){
    return question->answers;
}

void question_add_answer(QUESTION question, ANSWER answer){
    answer_set_parent_ptr(answer, question);
    question->answers = g_slist_prepend(question->answers, answer);
}

void question_destroy(QUESTION question){
    dateTime_destroy (question->date);
    xmlFree(question->title);
    xmlFree(question->tags);
    xmlFree(question->ownerName);
    g_slist_free(question->answers);
    free(question);
}

void question_destroy_generic(gpointer question){
    question_destroy((QUESTION) question);
}
