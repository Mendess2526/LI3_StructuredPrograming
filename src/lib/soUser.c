#include "soUser.h"
#include <stdlib.h>

#define INT_CMP(a,b) ((a > b) - (a < b))

typedef GSList * POSTS;

struct _so_user{
    int reputation;
    int nrPosts;
    long id;
    xmlChar *name;
    xmlChar *bio;
    POSTS posts;
};

gint postTimeCompare(gconstpointer a, gconstpointer b){
    DATETIME dataA = post_get_date((POST) b);
    DATETIME dataB = post_get_date((POST) a);
    int c;
    c = INT_CMP(dateTime_get_horas(dataA),         dateTime_get_horas(dataB));
    if(c) return c;
    c = INT_CMP(dateTime_get_minutos(dataA),       dateTime_get_minutos(dataB));
    if(c) return c;
    c = INT_CMP(dateTime_get_segundos(dataA),      dateTime_get_segundos(dataB));
    if(c) return c;
    c = INT_CMP(dateTime_get_milissegundos(dataA), dateTime_get_milissegundos(dataB));
    if(c) return c;
    return 0;
}

SO_USER so_user_create(long id, int reputation, xmlChar *name, xmlChar *bio){
    SO_USER user = malloc (sizeof(struct _so_user));
    user->id = id;
    user->reputation = reputation;
    user->nrPosts = 0;
    user->name = xmlStrdup(name);
    user->bio = xmlStrdup(bio);
    user->posts = NULL;
    return user;
}


long so_user_get_id(SO_USER user){
    return user->id;
}

int so_user_get_reputation(SO_USER user){
    return user->reputation;
}

xmlChar *so_user_get_name(SO_USER user){
    return xmlStrdup(user->name);
}

xmlChar *so_user_get_bio(SO_USER user){
    return xmlStrdup(user->bio);
}

int so_user_get_post_count(SO_USER user){
    return user->nrPosts;
}

POSTS so_user_get_posts(SO_USER user){
    return user->posts;
}

void so_user_add_post(SO_USER user, POST post){
    user->posts = g_slist_insert_sorted(user->posts, post, postTimeCompare);
   user->nrPosts++;
}

void so_user_destroy(SO_USER user){
    xmlFree(user->name);
    xmlFree(user->bio);
    g_slist_free_full(user->posts, post_destroy_generic); 
    free(user);
}

void so_user_destroy_generic(gpointer user){
    so_user_destroy((SO_USER) user);
}