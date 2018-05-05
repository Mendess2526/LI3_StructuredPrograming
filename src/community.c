#include "community.h"
#include "question.h"
#include "answer.h"
#include "calendario.h"
#include "dateTime.h"

#include <stdlib.h>

/** Hashtable de questões. */
typedef GHashTable* QUESTIONS_HTABLE;
/** Hashtable de respostas. */
typedef GHashTable* ANSWERS_HTABLE;
/** Hashtable de users. */
typedef GHashTable* SO_USERS_HTABLE;
/** Hashtable de tags. */
typedef GHashTable* TAGS_HTABLE;

/** Tipo concreto de dados para guardar questões, respostas, users e tags. */
struct TCD_community{
    QUESTIONS_HTABLE questions;     /**< Hashtable de questões. */
    ANSWERS_HTABLE answers;         /**< Hashtable de respostas. */
    SO_USERS_HTABLE users;          /**< Hashtable de users. */
    TAGS_HTABLE tags;               /**< Hashtable de tags. */
    CALENDARIO calendarioQuestions; /**< Calendário para guardar questões. */
    CALENDARIO calendarioAnswers;   /**< Calendário para guardar respostas. */
};

/**
 * Aloca um id.
 * @param val O valor a alocar.
 * @returns Um id alocado.
 */
static inline gint64* newId(long val);

/**
 * Atualiza os posts de um user.
 * @param users Os users.
 * @param ownerId O user que vais atualizar.
 * @param post O post do user.
 */
static inline void updateUserPosts(SO_USERS_HTABLE users,
                                   long ownerId,
                                   POST post);

/**
 * Atualiza as respostas da questão.
 * @param com Uma instância da estrutura.
 * @param answer A resposta a adicionar.
 */
static inline void updateQuestionAnswers(TAD_community com, ANSWER answer);

/**
 * Coleciona ordenadamente elementos da TCD.
 * @param value Elemento da TCD.
 * @param user_data Informação do utilizador.
 * @returns 1 para percorrer todos os elementos pedidos.
 */
static int collect(void* value, void* user_data);

/**
 * Coleciona ordenadamente elementos da TCD.
 * @param value Elemento da TCD.
 * @param user_data Informação do utilizador.
 * @returns 1 para percorrer todos os elementos pedidos.
 */
static int collect_with_data(void* value, void* user_data);

/**
 * Chama a função de coleção de elementos ignorando a key.
 * @param key Chave do elemento (ignorado).
 * @param value Elemento da TCD.
 * @param user_data Informação do utilizador.
 */
static void collect_key_value(gpointer key, gpointer value, gpointer user_data);

/**
 * Filtra elementos da TCD.
 * @param value Elemento da TCD.
 * @param user_data Informação do utilizador.
 * @returns 1 se a lista ainda não está cheia, 0 caso contrário.
 */
static int filter(gpointer elem, gpointer user_data);

static inline gint64* newId(long val){
    gint64* id = g_new(gint64, 1);
    *id = val;
    return id;
}

static inline void updateUserPosts(SO_USERS_HTABLE users,
                                   long ownerId,
                                   POST post){
    SO_USER user = g_hash_table_lookup(users, &ownerId);
    if(user) so_user_add_post(user, post);
}

static inline void updateQuestionAnswers(TAD_community com, ANSWER answer){
    long parentId = answer_get_parent_id(answer);
    QUESTION question = g_hash_table_lookup(com->questions,
            (gconstpointer) &parentId);
    if(question) question_add_answer(question, answer);
}

TAD_community init(){
    return community_create();
}

TAD_community community_create(){
    TAD_community com = (TAD_community) malloc(sizeof(struct TCD_community));
    com->questions = g_hash_table_new_full(
            g_int64_hash, g_int64_equal, g_free, question_destroy_generic);

    com->answers = g_hash_table_new_full(
            g_int64_hash, g_int64_equal, g_free, answer_destroy_generic);

    com->users = g_hash_table_new_full(
            g_int64_hash, g_int64_equal, g_free, so_user_destroy_generic);
    com->tags = g_hash_table_new_full(
            g_str_hash, g_str_equal, g_free, g_free);
    com->calendarioQuestions = calendario_create(11, question_date_cmp, NULL);
    com->calendarioAnswers = calendario_create(11, answer_date_cmp, NULL);
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
    gint64* id = newId(question_get_id(question));

    g_hash_table_insert(com->questions, (gpointer) id, question);

    calendario_add_post(com->calendarioQuestions, question,
            question_get_date(question));

    updateUserPosts(com->users, question_get_owner_id(question),
            post_create(QUESTION_T, question));
}

void community_add_answer(TAD_community com, ANSWER answer){
    gint64* id = newId(answer_get_id(answer));

    g_hash_table_insert(com->answers, (gpointer) id, answer);

    calendario_add_post(com->calendarioAnswers, answer,
            answer_get_date(answer));

    updateQuestionAnswers(com, answer);
    updateUserPosts(com->users, answer_get_owner_id(answer),
            post_create(ANSWER_T, answer));
}

void community_add_user(TAD_community com, SO_USER user){
    gint64* id = newId(so_user_get_id(user));

    g_hash_table_insert(com->users, (gpointer) id, user);
}

void community_add_tag(TAD_community com, long id, const xmlChar* tag){
    gint64* id_aloc = newId(id);

    g_hash_table_insert(com->tags, xmlStrdup(tag), id_aloc);
}

QUESTION community_get_question(TAD_community com, long id){
    return g_hash_table_lookup(com->questions, (gconstpointer) &id);
}

ANSWER community_get_answer(TAD_community com, long id){
    return g_hash_table_lookup(com->answers, (gconstpointer) &id);
}

SO_USER community_get_user(TAD_community com, long id){
    return g_hash_table_lookup(com->users, (gconstpointer) &id);
}

long community_get_user_count(TAD_community com){
    return g_hash_table_size(com->users);
}

long community_get_question_count(TAD_community com){
    return g_hash_table_size(com->questions);
}

long community_get_answer_count(TAD_community com){
    return g_hash_table_size(com->answers);
}

/** Estrutura usada para colecionar elementos da TCD durante iterações. */
typedef struct _collector{
    GSList* list;    /**< Lista de elementos. */
    ComCmpFunc func; /**< Função para ordenar os elementos na lista. */
    int maxSize;     /**< Tamanho maximo da lista. */
}* COLLECTOR;

static int collect(void* value, void* user_data){
    COLLECTOR col = (COLLECTOR) user_data;
    if(col->list == NULL || (*col->func)(col->list->data, value) < 0){
        col->list = g_slist_prepend(col->list, value);
    }else{
        int i = 0;
        for(GSList* cur = col->list;
            cur && i < col->maxSize; cur = cur->next, ++i){
            if(!cur->next || (*col->func)(cur->next->data, value) < 0){
                cur->next = g_slist_prepend(cur->next, value);
                i = col->maxSize;
            }
        }
    }
    return 1;
}

/**
 * Estrutura usada para colecionar elementos da TCD durante iterações, guardando
 * informação extra, que é passada à função de comparação.
 */
typedef struct _collector_with_data{
    GSList* list;         /**< Lista de elementos. */
    ComGetValueFunc func; /**< Função para determinar a posição na lista. */
    void* data;           /**< Informação extra passada à função de comparação. */
    int maxSize;          /**< Tamanho máximo da lista. */
}* COLLECTOR_WITH_DATA;

typedef struct _col_pair{
    int value;
    void* elem;
}* COLLECTOR_PAIR;

COLLECTOR_PAIR col_pair_create(int value, void* elem){
    COLLECTOR_PAIR clp = malloc(sizeof(struct _col_pair));
    clp->value = value;
    clp->elem = elem;
    return clp;
}

static int collect_with_data(void* value, void* user_data){
    COLLECTOR_WITH_DATA col = (COLLECTOR_WITH_DATA) user_data;
    int cmpValue = (*col->func)(value, col->data);
    COLLECTOR_PAIR pair = (COLLECTOR_PAIR) col->list->data;
    if(col->list == NULL || pair->value < cmpValue){
        col->list = g_slist_prepend(col->list,
                col_pair_create(cmpValue, value));
    }else{
        int i = 0;
        for(GSList* cur = col->list;
            cur && i < col->maxSize; cur = cur->next, ++i){
            pair = (COLLECTOR_PAIR) cur->next->data;
            if(!cur->next || pair->value < cmpValue){
                cur->next = g_slist_prepend(cur->next,
                        col_pair_create(cmpValue, value));
                i = col->maxSize;
            }
        }
    }
    return 1;
}

static void collect_key_value(gpointer key, gpointer value, gpointer user_data){
    (void) key;
    collect(value, user_data);
}

USERS community_get_sorted_user_list(TAD_community com, ComCmpFunc func, int N){
    COLLECTOR col = malloc(sizeof(struct _collector));
    col->func = func;
    col->list = NULL;
    col->maxSize = N;
    g_hash_table_foreach(com->users, collect_key_value, col);
    USERS r = col->list;
    free(col);
    return r;
}

QUESTIONS community_get_sorted_question_list(TAD_community com,
                                             DATETIME from,
                                             DATETIME to,
                                             ComCmpFunc func,
                                             int N){
    COLLECTOR col = malloc(sizeof(struct _collector));
    col->func = func;
    col->list = NULL;
    col->maxSize = N;
    calendario_iterate(com->calendarioQuestions, from, to, col, collect);
    QUESTIONS r = col->list;
    free(col);
    return r;
}

QUESTIONS community_get_sorted_question_list_with_data(TAD_community com,
                                                       DATETIME from,
                                                       DATETIME to,
                                                       ComGetValueFunc func,
                                                       int N,
                                                       void* compare_data){
    COLLECTOR_WITH_DATA col = malloc(sizeof(struct _collector_with_data));
    col->func = func;
    col->list = NULL;
    col->data = compare_data;
    col->maxSize = N;
    calendario_iterate(com->calendarioQuestions, from, to, col,
            collect_with_data);
    for(GSList* cur = col->list; cur; cur = cur->next){
        COLLECTOR_PAIR p = cur->data;
        cur->data = p->elem;
        free(p);
    }
    QUESTIONS r = col->list;
    free(col);
    return r;
}

ANSWERS community_get_sorted_answer_list(TAD_community com, DATETIME from,
                                         DATETIME to, ComCmpFunc func, int N){
    COLLECTOR col = malloc(sizeof(struct _collector));
    col->func = func;
    col->list = NULL;
    col->maxSize = N;
    calendario_iterate(com->calendarioAnswers, from, to, col, collect);
    ANSWERS r = col->list;
    free(col);
    return r;
}

/** Estrutura para colecionar elementos que cumprem uma certa condição. */
typedef struct _filter{
    int maxSize;        /**< Tamanho máximo da lista. */
    int load;           /**< Tamanho atual da lista. */
    void* filter_data;  /**< Informação do utilizador passada à função de filtragem. */
    ComFilterFunc func; /**< Função de filtragem. */
    GSList* last;       /**< Último elemento da lista. */
    GSList* list;       /**< Lista de elementos filtrados. */
}* FILTER;

static int filter(gpointer elem, gpointer user_data){
    FILTER filt = (FILTER) user_data;
    if(filt->load >= filt->maxSize) return 0;

    if((*filt->func)(elem, filt->filter_data)){
        if(filt->list == NULL){
            filt->list = g_slist_append(filt->list, elem);
            filt->last = filt->list;
        }else{
            filt->last = g_slist_append(filt->list, elem);
            filt->last = filt->last->next;
        }
        filt->load++;
    }
    return 1;
}

QUESTIONS community_get_filtered_questions(TAD_community com,
                                           DATETIME from,
                                           DATETIME to,
                                           int N,
                                           ComFilterFunc func,
                                           void* filter_data){
    FILTER f = (FILTER) malloc(sizeof(struct _filter));
    f->maxSize = N;
    f->load = 0;
    f->filter_data = filter_data;
    f->func = func;
    f->last = NULL;
    f->list = NULL;

    calendario_iterate(com->calendarioQuestions, from, to, f, filter);

    QUESTIONS qs = f->list;
    free(f);
    return qs;
}

long community_get_tag_id(TAD_community com, xmlChar* tag){
    long* id = g_hash_table_lookup(com->tags, (gconstpointer) tag);
    if(id) return *id;
    else return -2;
}

void community_iterate_questions(TAD_community com, DATETIME from,
                                 DATETIME to, void* data, CalFunc calFunc){
    calendario_iterate(com->calendarioQuestions, from, to, data, calFunc);
}

void community_iterate_answers(TAD_community com, DATETIME from, DATETIME to,
                               void* data, CalFunc calFunc){
    calendario_iterate(com->calendarioAnswers, from, to, data, calFunc);
}

/* --------------- PRINTING ------------------- */

/**
 * Função que é passada à hashtable de users para imprimir um user.
 * @param key Chave do valor na hashtable.
 * @param value Um User.
 * @param user_data String com o formato de impressão.
 */
static void printUser(gpointer key, gpointer value, gpointer user_data);

/**
 * Função que é passada à hashtable de questões para imprimir uma questão.
 * @param key Chave do valor na hashtable.
 * @param value Uma questão.
 * @param user_data String com o formato de impressão.
 */
static void printQuestion(gpointer key, gpointer value, gpointer user_data);

/**
 * Função que é passada à hashtable de repostas para imprimir uma reposta.
 * @param key Chave do valor na hashtable.
 * @param value Uma reposta.
 * @param user_data String com o formato de impressão.
 */
static void printAnswer(gpointer key, gpointer value, gpointer user_data);

/**
 * Função que é passada ao calendário para imprimir o id de uma questão.
 * @param question Questão à qual será extraído o id.
 */
static void cPrintQuestion(void* question);

/**
 * Função que é passada ao calendário para imprimir o id de uma resposta.
 * @param answer Resposta à qual será extraído o id.
 */
static void cPrintAnswer(void* answer);

void community_print_users(TAD_community com){
    g_hash_table_foreach(com->users, printUser,
            "Key{%08ld} User    {id:%3ld, reputation:%4d, name:%.5s, bio:%.5s}\n");
}

void community_print_questions(TAD_community com){
    g_hash_table_foreach(com->questions, printQuestion,
            "Key{%08ld} Question{id:%3ld, Date:%s, Title:%.5s, Score:%4d, AnswerCount:%4d, OwnerId:%3ld, OwnerName:%.5s}\n");
}

void community_print_answers(TAD_community com){
    g_hash_table_foreach(com->answers, printAnswer,
            "Key{%08ld} Answer  {id:%3ld, Date:%s, Score:%4d, ParentId:%3ld, OwnerId:%3ld, OwnerName:%.5s}\n");
}

void community_print_calendario(TAD_community com){
    printCalendario(com->calendarioQuestions, cPrintQuestion);
    printCalendario(com->calendarioAnswers, cPrintAnswer);
}

#define COLOR(idn) ((idn) == id ? "\033[32m" : "\033[31m")
#define RESET "\033[0m"

void community_print_thread(TAD_community com, long id){
    QUESTION q = g_hash_table_lookup(com->questions, &id);
    if(!q){
        ANSWER a = g_hash_table_lookup(com->answers, &id);
        if(!a){
            printf("Doesn't exist\n");
            return;
        }
        q = answer_get_parent_ptr(a);
    }else{
        long idn = question_get_id(q);
        printf("Id: %s%8ld"RESET", OwnerId: %8ld\n", COLOR(idn),
                question_get_id(q), question_get_owner_id(q));
        for(ANSWERS as = question_get_answers(q); as; as = as->next){
            idn = answer_get_id((ANSWER) as->data);
            printf("Id: %s%8ld"RESET", OwnerId: %8ld\n", COLOR(idn),
                    answer_get_id((ANSWER) as->data),
                    answer_get_owner_id((ANSWER) as->data));
        }
    }
}

static void printUser(gpointer key, gpointer value, gpointer user_data){
    long id = so_user_get_id((SO_USER) value);
    int reputation = so_user_get_reputation((SO_USER) value);
    xmlChar* name = so_user_get_name((SO_USER) value);
    xmlChar* bio = so_user_get_bio((SO_USER) value);
    printf((char*) user_data, *((gint64*) key), id, reputation, name, bio);
}

static void printQuestion(gpointer key, gpointer value, gpointer user_data){
    QUESTION question = (QUESTION) value;
    if(question == NULL){
        printf("NULL VALUE: Key:%ld\n", *((gint64*) key));
        return;
    }
    long id = question_get_id(question);
    DATETIME date = question_get_date(question);
    xmlChar* title = question_get_title(question);
    int score = question_get_score(question);
    int answerCount = question_get_answer_count(question);
    long ownerId = question_get_owner_id(question);
    char dateStr[11];
    if(date)
        sprintf(dateStr, "%02d:%02d:%4d",
                dateTime_get_day(date), dateTime_get_month(date),
                dateTime_get_year(date));
    else
        sprintf(dateStr, "(null)");
    printf((char*) user_data,
            *((long*) key), id, dateStr, title, score, answerCount, ownerId,
            NULL);
}

static void printAnswer(gpointer key, gpointer value, gpointer user_data){
    ANSWER answer = (ANSWER) value;
    if(answer == NULL){
        printf("NULL VALUE: Key:%ld\n", *((gint64*) key));
        return;
    }
    long id = answer_get_id(answer);
    DATETIME date = answer_get_date(answer);
    int score = answer_get_score(answer);
    long ownerId = answer_get_owner_id(answer);
    char dateStr[11];
    long parentId = answer_get_parent_id(answer);
    if(date)
        sprintf(dateStr, "%02d:%02d:%04d",
                dateTime_get_day(date), dateTime_get_month(date),
                dateTime_get_year(date));
    else
        sprintf(dateStr, "(null)");
    printf((char*) user_data,
            *((long*) key), id, dateStr, score, parentId, ownerId, NULL);
}

static void cPrintQuestion(void* question){
    printf("\t\t\t\tPost: %ld\n", question_get_id((QUESTION) question));
}

static void cPrintAnswer(void* answer){
    printf("\t\t\t\tPost: %ld\n", answer_get_id((ANSWER) answer));
}
