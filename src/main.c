#include <date.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "pair.h"
#include "community.h"
#include "common.h"

#include "str_rose_tree.h"

#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

/**
 * \brief Returns a string with the path to the dumps
 *
 * This function assumes that the dumps are inside a folder named "dump_exemplo"
 * in the home directory
 * If `folder_name` is NULL the default "askubuntu" is taken.
 *
 * Example:
 *  - executing without arguments (`./program`) will return
 *    "/home/<user-home>/dump_exemplo/askubuntu/
 *  - executing with arguments (`./program android`) returns
 *    "/home/<user-home>/dump_exemplo/android"
 *
 * @param folder_name The name of the folder inside `dump_exemplo/`
 * @returns The full path to the folder
 */
static char* makeDumpPath(const char* folder_name);
static void printAndDestroyStrPair(STR_pair sP);
static void printAndDestroyLongPair(LONG_pair lP);
static void printAndDestroyLongList(LONG_list lL, int size);
static void printAndDestroyUser(USER u);

int main(int argc, const char **argv){
    char *folder;
    if(argc > 1)
        folder = makeDumpPath(argv[1]);
    else
        folder = makeDumpPath(NULL);

    TAD_community com = init();
    com = load(com,folder);
    free(folder);

    Date beginingOfTime = createDate(1,1,1);
    Date theHeatDeath = createDate(30,11,9999);

    printf("%sQUERY  1:%s Info from Post %sParams [2]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyStrPair(info_from_post(com, 2));

    printf("%sQUERY  2:%s Top most active %sParams [5]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyLongList(top_most_active(com, 5), 5);

    printf("%sQUERY  3:%s Total Posts %sParams [1/1/2008, 30/11/9999]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyLongPair(total_posts(com, beginingOfTime, theHeatDeath));

    printf("%sQUERY  4:%s Questions with tag %sParams [sms, 1/1/2008, 30/11/9999]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyLongList(questions_with_tag(com, "sms", beginingOfTime, theHeatDeath), 3);

    printf("%sQUERY  5:%s Get user info %sParams [2]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyUser(get_user_info(com, 2));

    printf("%sQUERY  6:%s Most voted answer %sParams [5, 1/1/2008, 30/11/9999]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyLongList(most_voted_answers(com, 5, beginingOfTime, theHeatDeath), 5);

    printf("%sQUERY  7:%s Most answered questions %sParams [5, 1/1/12008, 30/11/9999]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyLongList(most_answered_questions(com, 5, beginingOfTime, theHeatDeath), 5);

    printf("%sQUERY  8:%s Contains word %sParams [message, 5]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyLongList(contains_word(com, "message", 5), 5);

    printf("%sQUERY  9:%s Both participated %sParams [10, 4, 5]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyLongList(both_participated(com, 10, 4, 5), 5);

    printf("%sQUERY 10:%s Better answer %sParams [1]%s\n",BLUE, RESET, GREEN, RESET);
    printf("Better answer: %ld\n", better_answer(com, 1));

    printf("%sQUERY 11:%s Most used best rep %sParams [5, 1/1/2008, 30/11/9999]%s\n",BLUE, RESET, GREEN, RESET);
    printAndDestroyLongList(most_used_best_rep(com, 5, beginingOfTime, theHeatDeath), 5);

    free_date(beginingOfTime);
    free_date(theHeatDeath);
    clean(com);
    return 0;
}

static char* makeDumpPath(const char* folder_name){
    char *home = getenv("HOME");
    char *dumps = "/dump_exemplo/";
    char *folder = NULL;
    if(!folder_name) folder = mystrdup("askubuntu/");
    else folder = mystrdup(folder_name);
    size_t len = strlen(home) + strlen(dumps) + strlen(folder) + 1;
    char* path = (char*) malloc(sizeof(char)*len);
    sprintf(path,"%s%s%s", home, dumps, folder);
    free(folder);
    return path;
}

static void printAndDestroyStrPair(STR_pair sP){
    if(!sP) return;
    char* s = get_fst_str(sP);
    printf("%sfst:%s %s\n", YELLOW, RESET, s);
    free(s);
    s = get_snd_str(sP);
    printf("%ssnd:%s %s\n", YELLOW, RESET, s);
    free(s);
    free_str_pair(sP);
}

static void printAndDestroyLongPair(LONG_pair lP){
    if(!lP) return;
    printf("%sfst:%s %ld\n", YELLOW, RESET, get_fst_long(lP));
    printf("%ssnd:%s %ld\n", YELLOW, RESET, get_snd_long(lP));
    free_long_pair(lP);
}

static void printAndDestroyLongList(LONG_list lL, int size){
    if(!lL) return;
    printf("%s[",YELLOW);
    for(int i = 0; i < size; i++){
        printf(" %8ld", get_list(lL, i));
        if(i<size-1) printf(",");
    }
    printf("]%s\n",RESET);
    free_list(lL);
}

static void printAndDestroyUser(USER u){
    if(!u) return;
    printf("bio: %s\n", get_bio(u));
    long *posts = get_10_latest_posts(u);
    for(int i=0; i<10; i++){
        printf("post[%d] -> %ld\n", i, posts[i]);
    }
    free(posts);
    free_user(u);
}
