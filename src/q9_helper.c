#include "question.h"
#include "q9_helper.h"

static long searchFromQuestion(QUESTION question, long id){
    if(question_get_owner_id(question) == id)
        return 1;

    ANSWERS answers = question_get_answers(question);
    for(; answers; answers = answers->next){
        if(answer_get_owner_id((ANSWER) answers->data) == id) return 1;
    }
    return 0;
}

long searchThread(POST post, long id){
    QUESTION q = NULL;
    if(post_is_answer(post))
        q = answer_get_parent_ptr(post_get_answer(post));
    else
        q = post_get_question(post);

    if(q == NULL) return -2;
    if(searchFromQuestion(q, id))
        return question_get_id(q);
    else
        return -2;
}
