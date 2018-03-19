#include "community.h"
#include "post.h"
#include <stdlib.h>

typedef struct _tcd_community{
    PERGUNTAS perguntas;
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
    com->perguntas    = g_hash_table_new_full(g_int64_hash,g_int64_equal,NULL,pergunta_destroy);
    com->users        = g_hash_table_new_full(g_int64_hash,g_int64_equal,NULL,so_user_destroy);
    return com;
}

void community_destroy(TAD_community com){
    g_hash_table_destroy(com->perguntas);
    g_hash_table_destroy(com->users);
    free(com);
}

void community_add_pergunta(TAD_community com, PERGUNTA pergunta){
    long id = pergunta_get_id(pergunta);
    //BEGIN merge pergunta in hash table
    long key = 0;
    PERGUNTA value = NULL;
    gboolean exists = g_hash_table_lookup_extended(
            com->users,
            (gconstpointer) &id,
            (gpointer) &key,
            (gpointer) &value
    );
    if(exists && value != NULL){
        pergunta = pergunta_merge(pergunta,value);
    }
    //END merge pergunta in hash table
    g_hash_table_insert(com->perguntas,(gpointer) &id,pergunta);
    updateUserPosts(com->users, (POST) pergunta);
}

void community_add_resposta(TAD_community com, RESPOSTA resposta){
    long key = 0L;
    PERGUNTA pergunta = NULL;
    long parentId = resposta_get_parent_id(resposta);
    gboolean found = g_hash_table_lookup_extended(
        com->perguntas,
        (gconstpointer) &parentId,
        (gpointer) &key,
        (gpointer) &pergunta
    );
    if(!found || !pergunta){
        long ownerId = resposta_get_owner_id(resposta);
        pergunta = pergunta_create_empty(ownerId);
        community_add_pergunta(com,pergunta);
    }
    pergunta_add_resposta(pergunta,resposta);
    updateUserPosts(com->users, (POST) resposta);
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
