#include "question.h"
#include <stdlib.h>

struct _question{
    int score;
    int answer_count;
    long id;
    long owner_id;
    DATETIME date;
    xmlChar *ownerName;
    xmlChar *title;
    xmlChar *tags;
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
    return q;
}

QUESTION question_create_empty(long id){
    QUESTION q = malloc(sizeof(struct _question));
    q->id=id;
    q->date = NULL;
    q->score = -1;
    q->owner_id = -2;
    q->title = NULL;
    q->tags = NULL;
    q->answer_count = -1;
    q->ownerName = NULL;
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

void question_destroy(QUESTION question){
    free(question->date);
    xmlFree(question->title);
    xmlFree(question->tags);
    xmlFree(question->ownerName);
    free(question);
}

void question_destroy_generic(gpointer question){
    question_destroy((QUESTION) question);
}

void question_add_answer(QUESTION question, ANSWER answer){
    
}

QUESTION question_merge(QUESTION oldQ, QUESTION newQ){
    if(oldQ->score == -1){
        oldQ->score = newQ->score;
    }
    if(oldQ->answer_count == -1){
        oldQ->answer_count = newQ->answer_count;
    }
    if(oldQ->owner_id == -2){
        oldQ->owner_id = newQ->owner_id;
    }
    if(oldQ->date == NULL){
        oldQ->date = newQ->date;
    }
    if(oldQ->title == NULL){
        oldQ->title = newQ->title;
    }
    if(oldQ->tags == NULL){
        oldQ->tags = newQ->tags;
    }
    if(oldQ->ownerName == NULL){
        oldQ->ownerName = newQ->ownerName;
    }
    question_destroy(newQ);
    return oldQ;
}