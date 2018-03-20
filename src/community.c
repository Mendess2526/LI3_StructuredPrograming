#include "community.h"
#include "post.h"
#include <stdlib.h>

typedef struct _tcd_community{
    QUESTIONS questions;
    SO_USERS users;
} TCD_community;

typedef TCD_community *TAD_community;

static void updateUserPosts(SO_USERS users, POST post){
    long id = post_get_id(post);
    long key = 0;
    SO_USER user = NULL;
    gboolean found = g_hash_table_lookup_extended(
            users,
            (gconstpointer) &id,
            (gpointer) &key,
            (gpointer) &user
    );
    if(!found || !user){
        long ownerId = post_get_owner_id(post);
        SO_USER user = so_user_create(ownerId,-1,NULL);
        g_hash_table_insert(users,(gpointer) &ownerId,user);
    }
    so_user_add_post(user,post);
}

TAD_community community_create(){
    TAD_community com = (TAD_community) malloc(sizeof(TCD_community));
    com->questions    = g_hash_table_new_full(g_int64_hash,g_int64_equal,NULL,question_destroy);
    com->users        = g_hash_table_new_full(g_int64_hash,g_int64_equal,NULL,so_user_destroy);
    return com;
}

void community_destroy(TAD_community com){
    g_hash_table_destroy(com->questions);
    g_hash_table_destroy(com->users);
    free(com);
}

void community_add_question(TAD_community com, QUESTION question){
    long id = question_get_id(question);
    //BEGIN merge question in hash table
    long key = 0;
    QUESTION value = NULL;
    gboolean exists = g_hash_table_lookup_extended(
            com->users,
            (gconstpointer) &id,
            (gpointer) &key,
            (gpointer) &value
    );
    if(exists && value != NULL){
        question = question_merge(question,value);
    }
    //END merge question in hash table
    g_hash_table_insert(com->questions,(gpointer) &id,question);
    updateUserPosts(com->users, (POST) question);
}

void community_add_answer(TAD_community com, ANSWER answer){
    long key = 0L;
    QUESTION question = NULL;
    long parentId = answer_get_parent_id(answer);
    gboolean found = g_hash_table_lookup_extended(
        com->questions,
        (gconstpointer) &parentId,
        (gpointer) &key,
        (gpointer) &question
    );
    if(!found || !question){
        long ownerId = answer_get_owner_id(answer);
        question = question_create_empty(ownerId);
        community_add_question(com,question);
    }
    question_add_answer(question,answer);
    updateUserPosts(com->users, (POST) answer);
}

void community_add_user(TAD_community com, SO_USER user){
    long id = so_user_get_id(user);
    //BEGIN merge user in hash table
    long key = 0;
    SO_USER value = NULL;
    gboolean exists = g_hash_table_lookup_extended(
            com->users,
            (gconstpointer) &id,
            (gpointer) &key,
            (gpointer) &value
    );
    if(exists && value != NULL){
        user = so_user_merge(user,value);
    }
    //END merge user in hash table
    g_hash_table_insert(com->users, (gpointer) &id, user);
}
