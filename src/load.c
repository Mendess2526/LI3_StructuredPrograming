#include "load.h"
#include "question.h"
#include "answer.h"
#include "dateTime.h"

#include <string.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>

#define POSTS "Posts.xml"
#define VOTES "Votes.xml"
#define USERS "Users.xml"

static inline int postStrcmp(const xmlChar *attribute);

static inline int userStrcmp(const xmlChar *attribute);

static inline int voteStrcmp(const xmlChar *attribute);

static inline DATETIME parseDate(const xmlChar *dateStr);

void start_post_element(void *user_data, const xmlChar *name, const xmlChar **attrs){
    if(name[0] == 'p') return;
    TAD_community com = (TAD_community) user_data;
    int numAttr = 9;
    long id = -2, owner_id = -2;
    int score = 0, comment_count = 0;
    DATETIME date = NULL;
    xmlChar *owner_name = NULL;
    //question attr
    xmlChar *title = NULL;
    xmlChar *tags = NULL;
    int answer_count = 0;
    //answer attr
    long parentId = -2;
    //boolean
    int postType = 0;
    for(;numAttr > 0 && attrs!=NULL && attrs[0]!=NULL;attrs += 2){
        int atrType = postStrcmp(attrs[0]);
        switch(atrType){
            case 1: id = strtol((char *) attrs[1],NULL,10);
                    numAttr--;
                    break;
            case 2: owner_id = strtol((char *) attrs[1],NULL,10);
                    numAttr--;
                    break;
            case 3: score = atoi((char *) attrs[1]);
                    numAttr--;
                    break;
            case 4: comment_count = atoi((char *) attrs[1]);
                    numAttr--;
                    break;
            case 5: date = parseDate(attrs[1]);
                    numAttr--;
                    break;
            case 6: owner_name = xmlStrdup(attrs[1]);
                    numAttr--;
                    break;
            case 10: title = xmlStrdup(attrs[1]);
                     numAttr--;
                     postType = 1;
                     break;
            case 11: tags = xmlStrdup(attrs[1]);
                     numAttr--;
                     postType = 1;
                     break;
            case 12: answer_count = atoi((char *) attrs[1]);
                     numAttr--;
                     postType = 1;
                     break;
            case 20: parentId = strtol((char *) attrs[1],NULL,10);
                     numAttr-=3;
                     postType = 2;
                     break;
            default: break;
        }
    }
    if(postType == 1){
        community_add_question(
                com,
                question_create(id,date,score,owner_id,title,tags,answer_count,owner_name));
    }else if(postType == 2){
        community_add_answer(
                com,
                answer_create(id,date,score,owner_id,parentId,owner_name,comment_count));
    }
}

void start_user_element(void *user_data, const xmlChar *name, const xmlChar **attrs){
    if(name[0] == 'u') return;
    TAD_community com = (TAD_community) user_data;
    int numAttr = 4;
    long id = -2;
    int reputation = 0;
    xmlChar *displayName = NULL;
    xmlChar *bio = NULL;
    for(;numAttr > 0 && attrs!=NULL && attrs[0]!=NULL;attrs += 2){
        int atrType = userStrcmp(attrs[0]);
        switch(atrType){
            case 1: id = strtol((char *) attrs[1],NULL,10);
                    numAttr--;
                    break;
            case 2: reputation = atoi((char *) attrs[1]);
                    numAttr--;
                    break;
            case 3: displayName = xmlStrdup(attrs[1]);
                    numAttr--;
                    break;
            case 4: bio = xmlStrdup(attrs[1]);
                    numAttr--;
                    break;
            default: break;
        }
    }
    community_add_user(com,so_user_create(id,reputation,displayName,bio));
}

void start_vote_element(void *user_data, const xmlChar *name, const xmlChar **attrs){
    if(name[0] == 'v') return;
    TAD_community com = (TAD_community) user_data;
    int numAttr = 2;
    long id = -2;
    int isFavorite = 0;
    for(;numAttr > 0 && attrs!=NULL && attrs[0]!=NULL;attrs += 2){
        int atrType = voteStrcmp(attrs[0]);
        switch(atrType){
            case 1: id = strtol((char *) attrs[1],NULL,10);
                    numAttr--;
                    break;
            case 2: if(atoi((char *) attrs[1]) == 5)
                        isFavorite = 1;
                    numAttr--;
                    break;
        }
    }
    if(isFavorite) community_add_favorite(com,id);
}

void error_handler(void *user_data, const char *msg, ...) {
    user_data=0;
    va_list args;
    va_start(args, msg);
    g_logv("XML", G_LOG_LEVEL_CRITICAL, msg, args);
    va_end(args);
}

TAD_community load(TAD_community com, char *dump_path){
    int n;
    char xmlPath[strlen(dump_path)+9];
    // sax handler
    xmlSAXHandler saxH;
    memset(&saxH,0,sizeof(xmlSAXHandler));
    saxH.error = error_handler;

    // parse users
    sprintf(xmlPath,"%s%s",dump_path,USERS);

    saxH.startElement = start_user_element;

    if((n=xmlSAXUserParseFile(&saxH,com,xmlPath))){
        fprintf(stderr,"Couldn't parse xml for file %s. Error: %d",USERS,n);
        return com;
    }

    // parse posts
    sprintf(xmlPath,"%s%s",dump_path,POSTS);

    saxH.startElement = start_post_element;

    if((n=xmlSAXUserParseFile(&saxH,com,xmlPath))){
        fprintf(stderr,"Couldn't parse xml for file %s. Error: %d",POSTS,n);
        return com;
    }

    // parse votes
    sprintf(xmlPath,"%s%s",dump_path,VOTES);

    saxH.startElement = start_vote_element;

    if((n=xmlSAXUserParseFile(&saxH,com,xmlPath))){
        fprintf(stderr,"Couldn't parse xml for file %s. Error: %d",VOTES,n);
        return com;
    }
    return com;
}


static inline int postStrcmp(const xmlChar *attribute){
    switch(attribute[0]){
        case 'I': return 1;                          // Id
        case 'O': switch(attribute[5]){
                      case 'U': return 2;            // OwnerUserId
                      case 'D': return 6;            // OwnerDisplayName
                  };
        case 'S': return 3;                          // Score
        case 'C': switch(attribute[6]){
                      case 't': return 4;            // CommentCount
                      case 'o': return 5;            // CreationDate
                  };
        case 'T': switch(attribute[1]){
                      case 'i': return 10;           // Title
                      case 'a': return 11;           // Tags
                  };
        case 'A': if(attribute[1] == 'n') return 12; // AnswerCount
        case 'P': if(attribute[1] == 'a') return 20; // ParentId

        default: return 0;
    }
}

static inline int userStrcmp(const xmlChar *attribute){
    switch(attribute[0]){
        case 'I': return 1;                       // Id
        case 'R': return 2;                       // Reputation
        case 'D': if(attribute[1]=='i') return 3; // DisplayName
        case 'A': if(attribute[1]=='b') return 4; // AboutMe

        default: return 0;
    }
}

static inline int voteStrcmp(const xmlChar *attribute){
    switch(attribute[0]){
        case 'P': return 1; // PostId
        case 'V': return 2; // VoteTypeId

        default: return 0;
    }
}

static inline DATETIME parseDate(const xmlChar *dateStr){
    int year, month, day, hour, minute, seconds, milisseconds;
    sscanf((char *) dateStr,"%d-%d-%dT%d:%d:%d.%d",&year,&month,&day,&hour,&minute,&seconds,&milisseconds);
    return dateTime_create(year,month,day,hour,minute,seconds,milisseconds);
}

