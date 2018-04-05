#include "community.h"
#include "question.h"
#include "answer.h"
#include "calendario.h"
#include "dateTime.h"

#include <stdlib.h>

typedef GHashTable* QUESTIONS;
typedef GHashTable* ANSWERS;
typedef GHashTable* SO_USERS;
typedef GHashTable* TAGS;

struct TCD_community{
    QUESTIONS questions;
    ANSWERS answers;
    SO_USERS users;
    TAGS tags;
    CALENDARIO calendarioQuestions;
    CALENDARIO calendarioAnswers;
};

gint questionTimeCompare(gconstpointer a, gconstpointer b){
    DATETIME dataA = question_get_date((QUESTION) b);
    DATETIME dataB = question_get_date((QUESTION) a);
    return dateTime_compare(dataA,dataB);
}

gint answerTimeCompare(gconstpointer a, gconstpointer b){
    DATETIME dataA = answer_get_date((ANSWER) b);
    DATETIME dataB = answer_get_date((ANSWER) a);
    return dateTime_compare(dataA, dataB);
}

/**
 * Aloca um id.
 * @param val O valor a alocar.
 * @returns Um id alocado.
 */
static inline gint64 *newId(long val){
    gint64 *id = g_new(gint64, 1);
    *id = val;
    return id;
}

/**
 * Atualiza os posts de um user.
 * @param users Os users a atualizar.
 * @param post O post do user.
 */
static inline void updateUserPosts(SO_USERS users, long ownerId, POST post){
    SO_USER user = g_hash_table_lookup(users, &ownerId);
    if(user) so_user_add_post(user,post);
}

/**
 * Atualiza as resposta das perguntas.
 * @param com Uma instancia da estrutura.
 * @param answer A resposta a adicionar.
 */
static inline void updateQuestionsAnswers(TAD_community com, ANSWER answer){
    long parentId = answer_get_parent_id(answer);
    QUESTION question = g_hash_table_lookup(com->questions, (gconstpointer) &parentId);
    if(question) question_add_answer(question,answer);
}

//TODO me no like this
TAD_community init(){
    return community_create();
}

TAD_community community_create(){
    TAD_community com = (TAD_community) malloc(sizeof(struct TCD_community));
    com->questions  = g_hash_table_new_full(
            g_int64_hash, g_int64_equal, g_free, question_destroy_generic);

    com->answers    = g_hash_table_new_full(
            g_int64_hash, g_int64_equal, g_free, answer_destroy_generic);

    com->users      = g_hash_table_new_full(
            g_int64_hash, g_int64_equal, g_free, so_user_destroy_generic);
    com->tags = g_hash_table_new_full(
            g_str_hash, g_str_equal, g_free, g_free);
    com->calendarioQuestions = calendario_create(10, questionTimeCompare, NULL);
    com->calendarioAnswers   = calendario_create(10, answerTimeCompare, NULL);
    return com;
}

void community_destroy(TAD_community com){
    g_hash_table_destroy(com->questions);
    g_hash_table_destroy(com->answers);
    g_hash_table_destroy(com->users);
    g_hash_table_destroy(com->tags);
    calendario_destroy(com->calendarioQuestions);
    calendario_destroy(com->calendarioAnswers);
    free(com);
}

void community_add_question(TAD_community com, QUESTION question){
    gint64 *id = newId(question_get_id(question));

    g_hash_table_insert(com->questions, (gpointer) id, question);

    calendario_add_post(com->calendarioQuestions, question, question_get_date(question));

    updateUserPosts(com->users, question_get_owner_id(question), post_create(QUESTION_T, question));
}

void community_add_answer(TAD_community com, ANSWER answer){
    gint64 *id = newId(answer_get_id(answer));

    g_hash_table_insert(com->answers, (gpointer) id, answer);

    calendario_add_post(com->calendarioAnswers, answer, answer_get_date(answer));

    updateQuestionsAnswers(com,answer);
    updateUserPosts(com->users, answer_get_owner_id(answer), post_create(ANSWER_T, answer));
}

void community_add_user(TAD_community com, SO_USER user){
    gint64 *id = newId(so_user_get_id(user));

    g_hash_table_insert(com->users, (gpointer) id, user);
}

void community_add_tag(TAD_community com, long id, xmlChar* tag){
    gint64* id_aloc = newId(id);

    g_hash_table_insert(com->tags, (gpointer) tag, id_aloc);
}

QUESTION community_get_question(TAD_community com, long id){
    return g_hash_table_lookup(com->questions, (gconstpointer) &id);
}

ANSWER community_get_answer(TAD_community com, long id){
    return g_hash_table_lookup(com->answers, (gconstpointer) &id);
}

SO_USER community_get_user(TAD_community com, long id){
    return g_hash_table_lookup(com->users,(gconstpointer) &id);
}

long community_get_tag_id(TAD_community com, xmlChar* tag){
    long* id = g_hash_table_lookup(com->tags, (gconstpointer) tag);
    if(id) return *id;
    else return -2;
}

void community_iterate_questions(TAD_community com, Date from, Date to, void* data, GFunc calFunc){
    calendario_iterate(com->calendarioQuestions, from, to, data, calFunc);
}

void community_iterate_answers(TAD_community com, Date from, Date to, void* data, GFunc calFunc){
    calendario_iterate(com->calendarioAnswers, from, to, data, calFunc);
}

/* --------------- PRINTING ------------------- */

void printAnswer(gpointer key, gpointer value, gpointer user_data);
void printQuestion(gpointer key, gpointer value, gpointer user_data);
void printUser(gpointer key, gpointer value, gpointer user_data);

void printUser(gpointer key, gpointer value, gpointer user_data){
    long id = so_user_get_id((SO_USER) value);
    int reputation = so_user_get_reputation((SO_USER) value);
    xmlChar *name = so_user_get_name((SO_USER) value);
    xmlChar *bio = so_user_get_bio((SO_USER) value);
    printf((char *)user_data, *((gint64 *)key), id, reputation, name, bio);
}

void printUsers(TAD_community com){
    g_hash_table_foreach(com->users, printUser,
            "Key{%08ld} User    {id:%3ld, reputation:%4d, name:%.5s, bio:%.5s}\n");
}

void printQuestion(gpointer key, gpointer value, gpointer user_data){
    QUESTION question = (QUESTION) value;
    if(question == NULL){ printf("NULL VALUE: Key:%ld\n",*((gint64 *) key)); return;}
    long id = question_get_id(question);
    DATETIME date = question_get_date(question);
    xmlChar *title = question_get_title(question);
    int score = question_get_score(question);
    int answerCount = question_get_answer_count(question);
    long ownerId = question_get_owner_id(question);
    char dateStr[11];
    if(date)
        sprintf(dateStr, "%02d:%02d:%4d",
            dateTime_get_dia(date), dateTime_get_mes(date), dateTime_get_ano(date));
    else
        sprintf(dateStr,"(null)");
    printf((char *) user_data,
            *((long *) key), id, dateStr, title, score, answerCount, ownerId, NULL);
}

void printQuestions(TAD_community com){
    g_hash_table_foreach(com->questions, printQuestion,
            "Key{%08ld} Question{id:%3ld, Date:%s, Title:%.5s, Score:%4d, AnswerCount:%4d, OwnerId:%3ld, OwnerName:%.5s}\n");
}

void printAnswer(gpointer key, gpointer value, gpointer user_data){
    ANSWER answer = (ANSWER) value;
    if(answer == NULL){ printf("NULL VALUE: Key:%ld\n",*((gint64 *) key)); return;}
    long id = answer_get_id(answer);
    DATETIME date = answer_get_date(answer);
    int score = answer_get_score(answer);
    long ownerId = answer_get_owner_id(answer);
    char dateStr[11];
    long parentId = answer_get_parent_id(answer);
    if(date)
        sprintf(dateStr, "%02d:%02d:%04d",
            dateTime_get_dia(date), dateTime_get_mes(date), dateTime_get_ano(date));
    else
        sprintf(dateStr,"(null)");
    printf((char *) user_data,
            *((long *) key), id, dateStr, score, parentId, ownerId, NULL);
}

void printAnswers(TAD_community com){
    g_hash_table_foreach(com->answers, printAnswer,
            "Key{%08ld} Answer  {id:%3ld, Date:%s, Score:%4d, ParentId:%3ld, OwnerId:%3ld, OwnerName:%.5s}\n");
}

void cPrintQuestion(void* question){
    printf("\t\t\t\tPost: %ld\n", question_get_id((QUESTION) question));
}
void cPrintAnswer(void* answer){
    printf("\t\t\t\tPost: %ld\n",answer_get_id((ANSWER) answer));
}
void community_print_calendario(TAD_community com){
    printCalendario(com->calendarioQuestions, cPrintQuestion);
    printCalendario(com->calendarioAnswers, cPrintAnswer);
}
