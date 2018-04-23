#include "q3_helper.h"
#include "community.h"
#include "dateTime.h"

int calFun(void* elem, void* user_data){
    long* nr = (long*) user_data;
    *nr+= 1;
    return 1;
}

LONG_pair total_posts_helper(TAD_community com, Date begin, Date end){
    long nrQuestions = 0;
    long nrAnswers = 0;
    DATETIME from = dateTime_create(get_year(begin), get_month(begin), get_day(begin),0,0,0,0);
    DATETIME to = dateTime_create(get_year(end), get_month(end), get_day(end),23,59,59,999);

    community_iterate_answers(com, from, to, &nrAnswers, calFun);
    community_iterate_questions(com, from, to, &nrQuestions, calFun);

    dateTime_destroy(from);
    dateTime_destroy(to);

    return create_long_pair(nrQuestions,nrAnswers);
}
