#include "post.h"

struct _post{
    enum POST_TYPE type;
    void * c;
};

POST post_create(int type, void *c){
    POST p = (POST) malloc(sizeof(struct _post));
    p->type = type;
    p->c = c;
    return p;
}

int post_is_question(POST post){
    return post->type == QUESTION_T;
}

int post_is_answer(POST post){
    return post->type == ANSWER_T;
}

QUESTION post_get_question(POST post){
    if(post_is_question(post)){
        return (QUESTION) post->c;
    }
    return NULL;
}

ANSWER post_get_answer(POST post){
    if(post_is_answer(post)){
        return (ANSWER) post->c;
    }
    return NULL;
}

long post_get_id(POST post){
    long id = -2;
    if(post_is_question(post)){
        QUESTION question = post_get_question(post);
        id = question_get_id(question);
    }else if(post_is_answer(post)){
        ANSWER answer = post_get_answer(post);
        id = answer_get_id(answer);
    }
    return id;
}

DATETIME post_get_date(POST post){
    DATETIME data = NULL;
    if(post_is_question(post)){
        QUESTION question = post_get_question(post);
        data = question_get_date(question);
    }else if(post_is_answer(post)){
        ANSWER answer = post_get_answer(post);
        data = answer_get_date(answer);
    }
    return data;
}

int post_get_score(POST post){
    int score = -1;
    if(post_is_question(post)){
        QUESTION question = post_get_question(post);
        score = question_get_score(question);
    }else if(post_is_answer(post)){
        ANSWER answer = post_get_answer(post);
        score = answer_get_score(answer);
    }
    return score;
}

long post_get_owner_id(POST post){
    long id = -2;
    if(post_is_question(post)){
        QUESTION question = post_get_question(post);
        id = question_get_owner_id(question);
    }else if(post_is_answer(post)){
        ANSWER answer = post_get_answer(post);
        id = answer_get_owner_id(answer);
    }
    return id;
}

xmlChar *post_get_owner_name(POST post){
    xmlChar *owner_name = NULL;
    if(post_is_question(post)){
        QUESTION question = post_get_question(post);
        owner_name = question_get_owner_name(question);
    }else if(post_is_answer(post)){
        ANSWER answer = post_get_answer(post);
        owner_name = answer_get_owner_name(answer);
    }
    return owner_name;
}
