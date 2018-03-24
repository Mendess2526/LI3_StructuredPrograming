#include "community.h"
#include "question.h"
#include "answer.h"

#include <stdlib.h>

struct TCD_community{
    QUESTIONS questions;
    ANSWERS answers;
    SO_USERS users;
};

gint64 *newId(long val){
    gint64 *id = g_new(gint64, 1);
    *id = so_user_get_id(user);
    return id;
}

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
        SO_USER user = so_user_create(ownerId,-1,NULL,NULL);
        g_hash_table_insert(users,(gpointer) &ownerId,user);
    }
    so_user_add_post(user,post);
}

//TODO me no like this
TAD_community init(){
    return community_create();
}

TAD_community community_create(){
    TAD_community com = (TAD_community) malloc(sizeof(struct TCD_community));
    com->questions = g_hash_table_new_full(
            g_int64_hash, g_int64_equal,g_free,question_destroy_generic);
    com->answers   = g_hash_table_new_full(
            g_int64_hash, g_int64_equal,g_free,answer_destroy_generic);
    com->users     = g_hash_table_new_full(
            g_int64_hash, g_int64_equal,g_free,so_user_destroy_generic);
    return com;
}

void community_destroy(TAD_community com){
    g_hash_table_destroy(com->questions);
    g_hash_table_destroy(com->answers);
    g_hash_table_destroy(com->users);
    free(com);
}

static SO_USER mergeUserInHashTable(TAD_community com, SO_USER user, gint64 *id){
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
    return user;
}

void community_add_question(TAD_community com, QUESTION question){
    long *id = newId(question_get_id(question));
    //BEGIN merge post in hash table TODO abstract
    long key = 0;
    QUESTION newQuestion = NULL;
    gboolean exists = g_hash_table_lookup_extended(
            com->users,
            (gconstpointer) &id,
            (gpointer) &key,
            (gpointer) &newQuestion
    );
    if(exists && question != NULL){
        question = question_merge(question,newQuestion);
    }
    //END merge question in hash table
    g_hash_table_insert(com->questions,(gpointer) &id,question);
    updateUserPosts(com->users, (POST) question);
}

void community_add_answer(TAD_community com, ANSWER answer){
    long *id = newId(answer_get_id(answer));
    g_hash_table_insert(com->answers, (gpointer) &id, answer);
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
    gint64 *id = g_new(gint64, 1);
    *id = so_user_get_id(user);

    user = mergeUserInHashTable(com, user, id);
    
    g_hash_table_insert(com->users, (gpointer) &id, user);
}

//TODO think this through
void community_add_favorite(TAD_community com, long id){
    long key = -2;
    QUESTION question = NULL;
    gboolean exists = g_hash_table_lookup_extended(
            com->questions,
            (gconstpointer) &id,
            (gpointer) &key,
            (gpointer) &question
    );
    if(exists && question){
        return;
    }
    ANSWER answer = NULL;
    exists = g_hash_table_lookup_extended(
            com->questions,
            (gconstpointer) &id,
            (gpointer) &key,
            (gpointer) &answer
    );
    if(exists && answer){
        answer_add_favorite(answer);
    }
}

SO_USER community_get_user(TAD_community com, long id){
    return g_hash_table_lookup(com->users,(gconstpointer) &id);
}

void printUser(gpointer key, gpointer value, gpointer user_data){
    long id = so_user_get_id((SO_USER) value);
    int reputation = so_user_get_reputation((SO_USER) value);
    xmlChar *name = so_user_get_name((SO_USER) value);
    xmlChar *bio = so_user_get_bio((SO_USER) value);
    printf((char *)user_data, *((gint64 *)key), id, reputation, name, bio);
}

void printUsers(TAD_community com){
    g_hash_table_foreach(com->users, printUser, "Key{%ld} User{id:%ld, reputation:%ld, name:%ld, bio:%ld\n");
}