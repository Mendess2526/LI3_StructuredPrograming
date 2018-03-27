#include "soUser.h"
#include <stdlib.h>

struct _so_user{
    int reputation;
    long id;
    xmlChar *name;
    xmlChar *bio;
};

SO_USER so_user_create(long id,int reputation, xmlChar *name, xmlChar *bio){
    SO_USER user = malloc (sizeof(struct _so_user));
    user->id = id;
    user->reputation = reputation;
    user->name = xmlStrdup(name);
    user->bio = xmlStrdup(bio);
    return user;
}

SO_USER so_user_create_empty(long id){
    SO_USER user = malloc (sizeof(struct _so_user));
    user->id=id;
    user->reputation = -1;
    user->name = NULL;
    user->bio = NULL;
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

//TODO
void so_user_add_post(SO_USER user, POST post){
}

void so_user_destroy(SO_USER user){
    free(user->name);
    free(user->bio);
    free(user);
}

void so_user_destroy_generic(gpointer user){
    so_user_destroy((SO_USER) user);
}

SO_USER so_user_merge(SO_USER oldU, SO_USER newU){
    if(oldU->reputation == -1){
        oldU->reputation = newU->reputation;
    }
    if(oldU->name == NULL){
        oldU->name = newU->name;
    }
    if(oldU->bio == NULL){
        oldU->bio = newU->bio;
    }     
    so_user_destroy(newU);
    return oldU; 
}