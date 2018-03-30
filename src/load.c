#include "load.h"
#include "question.h"
#include "answer.h"
#include "dateTime.h"

#include <string.h>

#include <libxml/parser.h>
#include <libxml/parserInternals.h>

#define POSTS "/Posts.xml"
#define USERS "/Users.xml"

enum Post_attr{
    POST_ID,
    OWNER_USER_ID,
    SCORE,
    COMMENT_COUNT,
    CREATION_DATE,
    OWNER_DISPLAY_NAME,
    TITLE,
    TAGS,
    ANSWER_COUNT,
    PARENT_ID,
    POST_TYPE,
    POST_NONE
};

enum User_attr{
    USER_ID,
    REPUTATION,
    DISPLAY_NAME,
    ABOUT_ME,
    USER_NONE
};

static inline enum Post_attr postStrcmp(const xmlChar *attribute);

static inline enum User_attr userStrcmp(const xmlChar *attribute);

static inline DATETIME parseDate(const xmlChar *dateStr);

/**
 * Função passada ao saxHandler para fazer parse do ficheiro de posts
 * @param user_data Apontador generico usado para passar a instancia da estrutura
 * @param name Nome do elemento de xml encontrado
 * @param attrs Array de strings onde se encontram os atributos e respetivos valores
 */
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
            case USER_ID:
                    id = strtol((char *) attrs[1],NULL,10);
                    numAttr--;
                    break;
            case OWNER_USER_ID:
                    owner_id = strtol((char *) attrs[1],NULL,10);
                    numAttr--;
                    break;
            case SCORE:
                    score = atoi((char *) attrs[1]);
                    numAttr--;
                    break;
            case COMMENT_COUNT:
                    comment_count = atoi((char *) attrs[1]);
                    numAttr--;
                    break;
            case CREATION_DATE:
                    date = parseDate(attrs[1]);
                    numAttr--;
                    break;
            case OWNER_DISPLAY_NAME:
                    owner_name = xmlStrdup(attrs[1]);
                    numAttr--;
                    break;
            case TITLE:
                    title = xmlStrdup(attrs[1]);
                     numAttr--;
                     break;
            case TAGS:
                     tags = xmlStrdup(attrs[1]);
                     numAttr--;
                     break;
            case ANSWER_COUNT:
                     answer_count = atoi((char *) attrs[1]);
                     numAttr--;
                     break;
            case PARENT_ID:
                     parentId = strtol((char *) attrs[1],NULL,10);
                     numAttr-=3;
                     break;
            case POST_TYPE: postType = atoi((char *) attrs[1]);
                            if(postType != 1 && postType != 2)
                                return;
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

/**
 * Função passada ao saxHandler para fazer parse do ficheiro de users
 * @param user_data Apontador generico usado para passar a instancia da estrutura
 * @param name Nome do elemento de xml encontrado
 * @param attrs Array de strings onde se encontram os atributos e respetivos valores
 */
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
            case USER_ID:
                    id = strtol((char *) attrs[1],NULL,10);
                    numAttr--;
                    break;
            case REPUTATION:
                    reputation = atoi((char *) attrs[1]);
                    numAttr--;
                    break;
            case DISPLAY_NAME:
                    displayName = xmlStrdup(attrs[1]);
                    numAttr--;
                    break;
            case ABOUT_ME:
                    bio = xmlStrdup(attrs[1]);
                    numAttr--;
                    break;
            default: break;
        }
    }
    community_add_user(com,so_user_create(id,reputation,displayName,bio));
}

/**
 * Funcão que é chamada caso o xml estaja mal formatado
 * @param user_data Apontador generico usado para passar a instancia da estrutura
 * @param msg Mensagem de erro
 */
void error_handler(void *user_data, const char *msg, ...) {
    user_data=0;
    va_list args;
    va_start(args, msg);
    g_logv("XML", G_LOG_LEVEL_CRITICAL, msg, args);
    va_end(args);
}

/**
 * Carrega os dados dos ficheiros para um instancia da estrutura
 * @param com Instancia da estrutura
 * @param dump_path Caminho para a diretoria dos ficheiros
 * @returns A instancia da estrutura
 */
TAD_community load(TAD_community com, char *dump_path){
    int n;
    char xmlPath[strlen(dump_path)+10];
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
    xmlCleanupParser();
    return com;
}

/**
 * Retorna o atributo associado a string dada
 * @param attribute Atributo a testar
 * @return O enum do atributo correspondente
 */
static inline enum Post_attr postStrcmp(const xmlChar *attribute){
    switch(attribute[0]){
        case 'I': return POST_ID;
        case 'O': switch(attribute[5]){
                      case 'U': return OWNER_USER_ID;
                      case 'D': return OWNER_DISPLAY_NAME;
                  };
        case 'S': return SCORE;
        case 'C': switch(attribute[6]){
                      case 't': return COMMENT_COUNT;
                      case 'o': return CREATION_DATE;
                  };
        case 'T': switch(attribute[1]){
                      case 'i': return TITLE;
                      case 'a': return TAGS;
                  };
        case 'A': if(attribute[1] == 'n') return ANSWER_COUNT;
        case 'P': switch(attribute[1]){
                      case 'a': return PARENT_ID;
                      case 'o': return POST_TYPE;
                  };
        default: return POST_NONE;
    }
}

static inline enum User_attr userStrcmp(const xmlChar *attribute){
    switch(attribute[0]){
        case 'I': return USER_ID;
        case 'R': return REPUTATION;
        case 'D': if(attribute[1]=='i') return DISPLAY_NAME;
        case 'A': if(attribute[1]=='b') return ABOUT_ME;

        default: return USER_NONE;
    }
}

static inline DATETIME parseDate(const xmlChar *dateStr){
    int year, month, day, hour, minute, seconds, milisseconds;
    sscanf((char *) dateStr,"%d-%d-%dT%d:%d:%d.%d",&year,&month,&day,&hour,&minute,&seconds,&milisseconds);
    return dateTime_create(year,month-1,day-1,hour,minute,seconds,milisseconds);
}

