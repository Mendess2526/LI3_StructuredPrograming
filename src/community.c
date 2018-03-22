#include "community.h"
#include "question.h"
#include "answer.h"

#include <stdlib.h>

struct _tcd_community{
    QUESTIONS questions;
    ANSWERS answers;
    SO_USERS users;
};

guint mySuperGoodHash(gconstpointer key){
    return ((guint) (*((long *)key)))+2;
}

gint mySuperGoodEqual(gconstpointer a, gconstpointer b){
    return mySuperGoodHash(a) == mySuperGoodHash(b);
}
/**
 * Atualiza os posts de um user.
 * @param users Os users a atualizar
 * @param post O post do user
 */
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

/**
 * Adiciona uma questão à estrutura.
 * @param com Uma instância da estrutura.
 * @param question A questão a adicionar.
 */
static void community_add_question(TAD_community com, QUESTION question){
    long id = question_get_id(question);
    //BEGIN merge post in hash table
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
/**
 * Adiciona uma resposta a estrutura
 * @param com Uma instância da estrutura.
 * @param answer A resposta a adicionar
 */
static void community_add_answer(TAD_community com, ANSWER answer){
    long id = answer_get_id(answer);
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
//TODO me no like this
TAD_community init(){
    return community_create();
}
/**
 * Cria uma instancia da estrutura
 * @returns Uma instancia da estrutura
 */
TAD_community community_create(){
    TAD_community com = (TAD_community) malloc(sizeof(struct _tcd_community));
    com->questions = g_hash_table_new_full(
            mySuperGoodHash, mySuperGoodEqual,NULL,question_destroy_generic);
    com->answers   = g_hash_table_new_full(
            mySuperGoodHash, mySuperGoodEqual,NULL,answer_destroy_generic);
    com->users     = g_hash_table_new_full(
            g_int64_hash,g_int64_equal,NULL,so_user_destroy_generic);
    return com;
}
/**
 * Liberta a memoria ocupada por uma instancia da estrutura
 * @param com Uma instância da estrutura.
 */
void community_destroy(TAD_community com){
    g_hash_table_destroy(com->questions);
    g_hash_table_destroy(com->answers);
    g_hash_table_destroy(com->users);
    free(com);
}

/**
 * Adiciona um post ao tipo abstrato de dados.
 * @param com Uma instância da estrutura.
 * @param post O post a adicionar
 */
void community_add_post(TAD_community com, POST post){
    if(post_get_type(post) == 1){
        community_add_question(com,(QUESTION) post);
    }else{
        community_add_answer(com,(ANSWER) post);
    }
}
/**
 * Adiciona um user ao tipo abstrato de dados.
 * @param com Uma instância da estrutura.
 * @param user O user a adicionar
 */
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

//TODO think this through
/**
 * Adiciona um favorito à contagem de favoritos de uma resposta.
 * Caso o id seja de uma pergunta a função não faz nada
 * @param com Uma instância da estrutura
 * @param id do post
 */
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
