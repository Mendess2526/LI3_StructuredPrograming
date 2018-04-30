#include "interface.h"
#include "soUser.h"
#include "community.h"
#include "question.h"
#include "answer.h"
#include "dateTimeInterval.h"
#include "str_rose_tree.h"

#include <string.h>
#include <limits.h>

static LONG_list gslist2llist(GSList* list, int maxSize);

// query 1
STR_pair info_from_post(TAD_community com, long id){
    QUESTION question = community_get_question(com, id);
    if(!question){
        ANSWER answer = community_get_answer(com, id);
        if(!answer) return NULL;
        question = answer_get_parent_ptr(answer);
        if(!question) return NULL;
    }
    char *name = (char *) question_get_owner_name(question);
    if(name == NULL){
        SO_USER user = community_get_user(com,
                question_get_owner_id(question));
        name = (char *) so_user_get_name(user);
    }
    return create_str_pair((char *) question_get_title(question), name);
}

// query 2
LONG_list top_most_active(TAD_community com, int N){
    USERS usr = community_get_sorted_user_list(com, so_user_post_count_cmp, N);
    LONG_list list = create_list(N+1);
    int i=0;
    while(usr && i<N){
        set_list(list, i++, so_user_get_id((SO_USER) usr->data));
        USERS tmp = usr;
        usr = usr->next;
        g_slist_free_1(tmp);
    }
    set_list(list, i, 0);
    g_slist_free(usr);
    return list;
}


// query 3
int calFun(void* elem, void* user_data){
    (void) elem;
    long* nr = (long*) user_data;
    *nr+= 1;
    return 1;
}
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    long nrQuestions = 0;
    long nrAnswers = 0;
    DATETIME from = dateTime_create(get_year(begin), get_month(begin), get_day(begin),0,0,0,0);
    DATETIME to = dateTime_create(get_year(end), get_month(end), get_day(end),23,59,59,999);

    community_iterate_answers(com, from, to, &nrAnswers, calFun);
    community_iterate_questions(com, from, to, &nrQuestions, calFun);

    dateTime_destroy(from);
    dateTime_destroy(to);

    return create_long_pair(nrQuestions, nrAnswers);
}

// query 4
static int generic_question_has_tag(void* elem, void* filter_data){
    return question_has_tag((QUESTION) elem, (char*) filter_data);
}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    DATETIME from = dateTime_create(get_year(end), get_month(end), get_day(end), 23, 59, 59, 999);
    DATETIME to = dateTime_create(get_year(begin), get_month(begin), get_day(begin), 0, 0, 0, 0);

    QUESTIONS qs = community_get_filtered_questions(com, from, to, INT_MAX, generic_question_has_tag, tag);

    LONG_list l = gslist2llist(qs, g_slist_length(qs));

    dateTime_destroy(from);
    dateTime_destroy(to);
    g_slist_free(qs);
    return l;
}

// query 5
USER get_user_info(TAD_community com, long id){
    SO_USER user = community_get_user(com, id);
    if(user==NULL) return NULL;
    char* bio = (char*) so_user_get_bio(user);
    POSTS posts = so_user_get_posts(user);
    long list[10];
    int i;
    for(i=0; i<10 && posts!=NULL; i++){
        POST post = (POST) posts->data;
        list[i] = post_get_id(post);
        posts = posts->next;
    }
    while(i<10)
        list[i++] = -1;

    return create_user(bio, list);
}

// query 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
    DATETIME from = dateTime_create(get_year(begin), get_month(begin), get_day(begin), 0, 0, 0, 0);
    DATETIME to = dateTime_create(get_year(end), get_month(end), get_day(end), 0, 0, 0, 0);

    ANSWERS as = community_get_sorted_answer_list(com, from, to, answer_score_cmp, N);

    LONG_list l = gslist2llist(as, N);

    dateTime_destroy(from);
    dateTime_destroy(to);
    g_slist_free(as);

    return l;
}

// query 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    DATETIME from = dateTime_create(get_year(begin), get_month(begin), get_day(begin), 0, 0, 0, 0);
    DATETIME to = dateTime_create(get_year(end), get_month(end), get_day(end), 23, 59, 59, 999);
    DATETIME_INTERVAL dti = dateTime_interval_create(from, to);

    QUESTIONS qs = community_get_sorted_question_list_with_data(com, from, to, (ComGetValueFunc) question_get_answer_count_between_dates, N, dti);

    LONG_list r = gslist2llist(qs, N);

    dateTime_interval_destroy_full(dti);

    g_slist_free(qs);

    return r;
}

static int generic_strstr(void* elem, void* filter_data){
    char* word = (char*) filter_data;
    char* title = (char*) question_get_title((QUESTION) elem);
    return strstr(title, word) != NULL;
}

// query 8
LONG_list contains_word(TAD_community com, char* word, int N){
    DATETIME from = dateTime_get_year2038();
    DATETIME to = dateTime_get_epoch();

    QUESTIONS qs = community_get_filtered_questions(com, from, to, N, generic_strstr, word);

    LONG_list list = gslist2llist(qs, N);

    dateTime_destroy(from);
    dateTime_destroy(to);
    g_slist_free(qs);
    return list;
}

// query 9
static int question_date_cmp_with_data(gconstpointer a, gconstpointer b, gpointer d){
    (void) d;
    return question_date_cmp(a,b);
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
    // Get the users
    SO_USER user1 = community_get_user(com, id1);
    SO_USER user2 = community_get_user(com, id2);
    if(!user1 || !user2){
        LONG_list l = create_list(1);
        set_list(l, 0, 0);
        return l;
    }
    // Pick the user with the least posts
    POSTS posts;
    long searchId;
    if(so_user_get_post_count(user1) < so_user_get_post_count(user2)){
        posts = so_user_get_posts(user1);
        searchId = id2;
    }else{
        posts = so_user_get_posts(user2);
        searchId = id1;
    }
    // Get the questions in which both participated
    GSequence* seq = g_sequence_new(NULL);
    long* ids = malloc(sizeof(long)*N);
    int i;
    for(i = 0; posts && i<N; posts = posts->next){
        QUESTION q = post_search_thread_for_user((POST) posts->data, searchId);
        if(q){
            int exists = 0;
            long qId = question_get_id(q);
            for(int j = 0; !exists && j < i; j++)
                if(ids[j] == qId) exists = 1;

            if(!exists){// Avoid repeats
                g_sequence_prepend(seq, q);
                ids[i++] = qId;
            }
        }
    }
    free(ids);
    LONG_list list = create_list(i == 0 ? 1 : i);
    // Sort the list
    g_sequence_sort(seq, question_date_cmp_with_data, NULL);
    // Add to the LONG_list for return
    GSequenceIter* it = g_sequence_get_begin_iter(seq);
    i = 0;
    while(i < N && !g_sequence_iter_is_end(it)){
        set_list(list, i++, question_get_id((QUESTION) g_sequence_get(it)));
        it = g_sequence_iter_next(it);
    }
    set_list(list, i, 0);
    g_sequence_free(seq);
    return list;
}

// query 10
long better_answer(TAD_community com, long id){
    QUESTION question = community_get_question(com,id);
    if(question == NULL) return 0;
    ANSWERS answers = question_get_answers(question);
    double bestP = 0;
    long idBest = -1;
    for(ANSWERS cur = answers;cur != NULL;cur = cur->next){
        int score = answer_get_score(cur->data);
        long idAnswer = answer_get_id(cur->data);
        long idUser = answer_get_owner_id(cur->data);
        SO_USER user = community_get_user(com,idUser);
        int rep = so_user_get_reputation(user);
        int nrCom = answer_get_comment_count(cur->data);
        double testScore = (score*0.65)+(rep*0.25)+(nrCom*0.1);
        if(testScore>bestP){
            bestP = testScore;
            idBest = idAnswer;
        }
    }
    return idBest;
}

// query 11
static void gather_tags(SO_USER usr, STR_ROSE_TREE rt, DATETIME from, DATETIME to){
    POSTS posts = so_user_get_posts(usr);
    for(; posts; posts = posts->next){
        DATETIME postDate = post_get_date(posts->data);
        int afterFrom = dateTime_compare(postDate, from) >= 0;
        int beforeTo = dateTime_compare(postDate, to)   <= 0;
        if(post_is_question(posts->data) && afterFrom && beforeTo){
            char** tags = question_get_tags((QUESTION) post_get_question(posts->data));
            for(int i=0; tags[i]; i++){
                str_rtree_add(rt, tags[i]);
                free(tags[i]);
            }
            free(tags);
        }
        if(!afterFrom) return;
    }
}

LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
    USERS users = community_get_sorted_user_list(com, so_user_reputation_cmp, N);

    DATETIME from = dateTime_create(get_year(begin), get_month(begin), get_day(begin), 0, 0, 0, 0);
    DATETIME to = dateTime_create(get_year(end), get_month(end), get_day(end), 23, 59, 59, 999);

    STR_ROSE_TREE rt = str_rtree_create();
    int n = 0;
    for(USERS cur = users; n++<N && cur; cur = cur->next){
        gather_tags(cur->data, rt, from, to);
    }
    g_slist_free(users);
    dateTime_destroy(from);
    dateTime_destroy(to);

    char** topTags = str_rtree_get_most_common_strings(rt, N);
    str_rtree_destroy(rt);

    LONG_list l = create_list(N+1);
    int i = 0;
    while(i < N && topTags[i]){
        set_list(l, i, community_get_tag_id(com,(xmlChar*) topTags[i]));
        free(topTags[i++]);
    }
    set_list(l, i, 0);
    free(topTags);

    return l;
}

TAD_community clean(TAD_community com){
    community_destroy(com);
    return NULL;
}

static inline LONG_list gslist2llist(GSList* list, int maxSize){
    LONG_list l = create_list(maxSize+1);
    for(int i=0; i<maxSize; i++) set_list(l, i, 0);
    int i = 0;
    for(; list && i<maxSize; list = list->next){
        set_list(l, i++, question_get_id(list->data));
    }
    set_list(l, i, 0);
    return l;
}
