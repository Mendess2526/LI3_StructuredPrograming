#include "q2_helper.h"
#include "community.h"

int postCountCmp(void* a, void* b){
    return so_user_get_post_count((SO_USER) a)
         - so_user_get_post_count((SO_USER) b);
}

LONG_list top_most_active_helper(TAD_community com, int N){
    USERS usr = community_get_sorted_user_list(com, postCountCmp, N);
    LONG_list list = create_list(N);
    for(int i=0; i<N; i++) set_list(list, i, 0);
    for(int i=0; usr && i<N; i++){
        set_list(list, i, so_user_get_id((SO_USER) usr->data));
        USERS tmp = usr;
        usr = usr->next;
        g_slist_free_1(tmp);
    }
    g_slist_free(usr);
    return list;
}
