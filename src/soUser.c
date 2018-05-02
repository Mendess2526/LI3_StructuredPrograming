#include "soUser.h"
#include "dateTime.h"

#include <stdlib.h>

struct _so_user{
    int reputation;
    int nrPosts;
    long id;
    xmlChar *name;
    xmlChar *bio;
    POSTS posts;
};

SO_USER so_user_create(long id, int reputation, const xmlChar *name, const xmlChar *bio){
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
    return user->name;
}

xmlChar *so_user_get_bio(SO_USER user){
    return user->bio;
}

int so_user_get_post_count(SO_USER user){
    return user->nrPosts;
}

POSTS so_user_get_posts(SO_USER user){
    return user->posts;
}

void so_user_add_post(SO_USER user, POST post){
    user->posts = g_slist_insert_sorted(user->posts, post, post_date_cmp);
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

int so_user_post_count_cmp(const void* a, const void* b){
    return ((SO_USER) a)->nrPosts - ((SO_USER) b)->nrPosts;
}

int so_user_reputation_cmp(const void* a, const void*b){
    return ((SO_USER) a)->reputation - ((SO_USER) b)->reputation;
}
