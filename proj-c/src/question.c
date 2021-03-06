#include "question.h"
#include "common.h"
#include "dateTimeInterval.h"

#include <stdlib.h>
#include <string.h>

struct _question{
    int score;
    int answer_count;
    long id;
    long owner_id;
    DATETIME date;
    xmlChar* ownerName;
    xmlChar* title;
    xmlChar* tags;
    ANSWERS answers;
};

QUESTION question_create(long id, DATETIME date, int score, long ownerId,
                         const xmlChar* title, const xmlChar* tags,
                         int answerCount, const xmlChar* ownerName){
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

xmlChar* question_get_title(QUESTION question){
    return question->title;
}

char** question_get_tags(QUESTION question){
    if(!question->tags || *question->tags == '\0') return NULL;
    xmlChar* tagsUnparsed = xmlStrdup(question->tags);
    char** result = malloc(sizeof(char*) * 6);
    memset(result, 0, sizeof(char*) * 6);
    char* token = strtok((char*) tagsUnparsed + 1, "><");
    int i = 0;
    while(token != NULL){
        result[i++] = mystrdup(token);
        token = strtok(NULL, "><");
    }
    free(tagsUnparsed);
    return result;
}

xmlChar* question_get_owner_name(QUESTION question){
    return question->ownerName;
}

int question_get_answer_count(QUESTION question){
    return question->answer_count;
}

int question_get_answer_count_between_dates(QUESTION question,
                                            DATETIME_INTERVAL dti){
    int i = 0;
    for(ANSWERS as = question->answers; as; as = as->next){
        if(dateTime_interval_is_between(dti,
                answer_get_date((ANSWER) as->data)))
            i++;
    }
    return i;
}

ANSWERS question_get_answers(QUESTION question){
    return question->answers;
}

void question_add_answer(QUESTION question, ANSWER answer){
    answer_set_parent_ptr(answer, question);
    question->answers = g_slist_prepend(question->answers, answer);
}

void question_destroy(QUESTION question){
    dateTime_destroy(question->date);
    xmlFree(question->title);
    xmlFree(question->tags);
    xmlFree(question->ownerName);
    g_slist_free(question->answers);
    free(question);
}

void question_destroy_generic(gpointer question){
    question_destroy((QUESTION) question);
}

int question_answer_count_cmp(const void* a, const void* b){
    return ((QUESTION) a)->answer_count - ((QUESTION) b)->answer_count;
}

int question_answer_count_cmp_with_dates(const void* a,
                                         const void* b,
                                         const void* dates){
    DATETIME_INTERVAL dti = (DATETIME_INTERVAL) dates;
    return question_get_answer_count_between_dates((QUESTION) a, dti)
           - question_get_answer_count_between_dates((QUESTION) b, dti);
}

int question_date_cmp(const void* a, const void* b){
    DATETIME dataA = question_get_date((QUESTION) b);
    DATETIME dataB = question_get_date((QUESTION) a);
    return dateTime_compare(dataA, dataB);
}

int question_has_tag(QUESTION question, char* tag){
    return strstr((char*) question->tags, tag) != NULL;
}
