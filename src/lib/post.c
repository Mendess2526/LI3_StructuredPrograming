#include "post.h"

#define TYPE_QUESTION 1
#define TYPE_ANSWER   2

struct _post{
    int type;
    void * c;
};

POST post_create(int type, void *c){
    POST p = malloc(sizeof(struct _post));
    p->type = type;
    p->c = c;
    return p;
}

int isQuestion(POST post){
    return post->type == TYPE_QUESTION;
}

int isAnswer(POST post){
    return post->type == TYPE_ANSWER;
}

QUESTION post_get_question(POST post){
    if(isQuestion(post)){
        return (QUESTION) post->c;
    }
    return NULL;
}

ANSWER post_get_answer(POST post){
    if(isAnswer(post)){
        return (ANSWER) post->c;
    }
    return NULL;
}
