#include "q11_helper.h"
#include "dateTime.h"
#include "str_rose_tree.h"

#include <libxml/parserInternals.h>

typedef struct tag_count_pair{
    char* tag;
    int count;
}TAG_COUNT_PAIR;


int repcmp(void* a, void*b){
    return so_user_get_reputation((SO_USER) b)
         - so_user_get_reputation((SO_USER) a);
}

static void gather_tags(SO_USER usr, STR_ROSE_TREE rt){
    POSTS posts = so_user_get_posts(usr);
    for(; posts; posts = posts->next){
        if(post_is_question(posts->data)){
            char** tags = question_get_tags((QUESTION) post_get_question(posts->data));
            for(int i=0; tags[i]; i++){
                str_rtree_add(rt, tags[i]);
                free(tags[i]);
            }
            free(tags);
        }
    }
}

LONG_list most_used_best_rep_helper(TAD_community com, int N, Date begin, Date end){
    USERS users = community_get_sorted_user_list(com, repcmp, N);
    STR_ROSE_TREE rt = str_rtree_create();
    for(USERS cur = users; cur; cur = cur->next){
        gather_tags(cur->data, rt);
    }
    g_slist_free(users);
    char** topTags = str_rtree_get_most_common_strings(rt, N);
    str_rtree_destroy(rt);
    LONG_list l = create_list(N);
    for(int i = 0; i < N; i++){
        set_list(l, i, community_get_tag_id(com,(xmlChar*) topTags[i]));
        free(topTags[i]);
    }
    free(topTags);

    return l;
}
