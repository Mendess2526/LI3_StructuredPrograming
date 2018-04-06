#include "question.h"
#include "q9_helper.h"

static long searchFromQuestion(QUESTION question, long id){
    if(question_get_owner_id(question) == id)
        return 1;

    ANSWERS answers = question_get_answers(question);
    if(answers == NULL) return 0;
    for(ANSWER answer = answers->data; answers; answers = answers->next){
        if(answer_get_owner_id(answer) == id) return 1;
    }
    return 0;
}

long searchThread(POST post, long id){
    QUESTION q = NULL;
    if(post_is_answer(post))
        q = answer_get_parent_ptr(post_get_answer(post));
    else
        q = post_get_question(post);

    if(searchFromQuestion(q, id))
        return question_get_id(q);
    else
        return -2;
}
