#include "interface.h"
#include "soUser.h"
#include "community.h"

// query 1
STR_pair info_from_post(TAD_community com, long id){
    QUESTION question = community_get_question(com, id);
    if(question){
        char *name = (char *) question_get_owner_name(question);
        if(name == NULL){
            SO_USER user = community_get_user(
                    com,
                    question_get_owner_id(question));
            name = (char *) so_user_get_name(user);
        }
        return create_str_pair((char *) question_get_title(question), name);
    }
    ANSWER answer = community_get_answer(com, id);
    if(answer){
        long qId = answer_get_parent_id(answer);
        return info_from_post(com, qId);
    }
    return NULL;
}
// query 2
LONG_list top_most_active(TAD_community com, int N){
    return NULL;
}

// query 3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    return NULL;
}

// query 4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    return NULL;
}

// query 5
USER get_user_info(TAD_community com, long id){
    return NULL;
}

// query 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
    return NULL;
}

// query 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    return NULL;
}

// query 8
LONG_list contains_word(TAD_community com, char* word, int N){
    return NULL;
}

// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
    return NULL;
}

// query 10
long better_answer(TAD_community com, long id){
    return 0L;
}

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
    return NULL;
}

TAD_community clean(TAD_community com){
    community_destroy(com);
    return NULL;
}