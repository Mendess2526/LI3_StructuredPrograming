#include "post.h"

#include <stdlib.h>
#include <limits.h>

struct _post{
    enum POST_TYPE type;
    void* c;
};

 /**
  * Verifica se um user é autor da questão ou alguma das respostas desta.
  * @param question Uma questão.
  * @param id Id do user.
  * @returns 1 se é o autor, 0 caso contrário.
  */
static int searchFromQuestion(QUESTION question, long id)

POST post_create(enum POST_TYPE type, void* c){
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
    int score = INT_MIN;
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

void post_destroy(POST post, int freeQorA){
    if(freeQorA){
        if(post->type == QUESTION_T)
            question_destroy_generic(post->c);
        else if(post->type == ANSWER_T)
            answer_destroy_generic(post->c);
    }
    free(post);
}

void post_destroy_generic(gpointer post){
    post_destroy((POST) post, 0);
}

static int searchFromQuestion(QUESTION question, long id){
    if(question_get_owner_id(question) == id)
        return 1;

    ANSWERS answers = question_get_answers(question);
    for(; answers; answers = answers->next){
        if(answer_get_owner_id((ANSWER) answers->data) == id) return 1;
    }
    return 0;
}

QUESTION post_search_thread_for_user(POST post, long id){
    QUESTION q = NULL;
    if(post_is_answer(post))
        q = answer_get_parent_ptr(post_get_answer(post));
    else
        q = post_get_question(post);

    if(q == NULL) return NULL;
    if(searchFromQuestion(q, id))
        return q;
    else
        return NULL;
}

int post_date_cmp(gconstpointer a, gconstpointer b){
    DATETIME dataA = post_get_date((POST) b);
    DATETIME dataB = post_get_date((POST) a);
    return dateTime_compare(dataA, dataB);
}