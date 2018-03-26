#include "soUser.h"

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

//falta
void so_user_add_post(SO_USER user, POST post){
}

void so_user_destroy(SO_USER user){
    free(user);
}

void so_user_destroy_generic(gpointer user){    
    so_user_destroy((SO_USER) user);
}
//should free memory

//TODO
SO_USER so_user_merge(SO_USER oldU, SO_USER newU){
    return NULL;
}