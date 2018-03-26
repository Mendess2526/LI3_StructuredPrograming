#include "post.h"

struct _post{
    int comment_count;
    int type;
    int score;
    long id;
    long owner_id;
    Date date;
    xmlChar *owner_display_name;
};


long post_get_id(POST post){
    return post->id;
}

Date post_get_date(POST post){
    return post->date;
}

int post_get_score(POST post){
    return post->score;
}

long post_get_owner_id(POST post){
    return post->owner_id;
}

int post_get_comment_count(POST post){
    return post->comment_count;
}

int post_get_type(POST post){
    return post->type;
}

xmlChar *post_get_owner_display_name(POST post){
    return xmlStrdup(post->owner_display_name);
}