#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "interface.h"
#include "pair.h"
#include "common.h"

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

    Date begin, end;

    printf("%sQUERY  1:%s Info from Post\n" ,BLUE, RESET);
    printf("%sParams [801049]%s\n", GREEN, RESET);
    printAndDestroyStrPair(info_from_post(com, 801049));
    printf("%sParams [796430]%s\n", GREEN, RESET);
    printAndDestroyStrPair(info_from_post(com, 796430));

    printf("%sQUERY  2:%s Top most active\n",BLUE, RESET);
    printf("\t%sParams [10]%s\n", GREEN, RESET);
    printAndDestroyLongList(top_most_active(com, 10), 10);
    printf("\t%sParams [100]%s\n", GREEN, RESET);
    printAndDestroyLongList(top_most_active(com, 100), 100);

    printf("%sQUERY  3:%s Total Posts\n",BLUE, RESET);
    printf("\t%sParams [1/7/2016, 31/07/2016]%s\n", GREEN, RESET);
    begin = createDate(0,6,2016);
    end = createDate(30,6,2016);
    printAndDestroyLongPair(total_posts(com, begin, end));
    free_date(begin);
    free_date(end);
    printf("\t%sParams [1/1/2014, 30/12/2014]%s\n", GREEN, RESET);
    begin = createDate(0,0,2014);
    end = createDate(30,11,2014);
    printAndDestroyLongPair(total_posts(com, begin, end));
    free_date(begin);
    free_date(end);

    printf("%sQUERY  4:%s Questions with tag\n",BLUE, RESET);
    printf("\t%sParams [package-management, 1/3/2013, 31/3/2013]%s\n", GREEN, RESET);
    begin = createDate(0,2,2013);
    end = createDate(30,2,2013);
    printAndDestroyLongList(questions_with_tag(com, "package-management", begin, end), -1);
    free_date(begin);
    free_date(end);
    printf("\t%sParams [nautilus, 1/1/2014, 31/1/2014]%s\n", GREEN, RESET);
    begin = createDate(0,0,2014);
    end = createDate(30,0,2014);
    printAndDestroyLongList(questions_with_tag(com, "nautilus", begin, end), -1);
    free_date(begin);
    free_date(end);

    printf("%sQUERY  5:%s Get user info\n",BLUE, RESET);
    printf("\t%sParams [314961]%s\n", GREEN, RESET);
    printAndDestroyUser(get_user_info(com, 314961));
    printf("\t%sParams [315025]%s\n", GREEN, RESET);
    printAndDestroyUser(get_user_info(com, 315025));

    printf("%sQUERY  6:%s Most voted answer",BLUE, RESET);
    printf("\t%sParams [5, 1/11/2015, 30/11/2015]%s\n", GREEN, RESET);
    begin = createDate(0,10,2015);
    end = createDate(29,10,2015);
    printAndDestroyLongList(most_voted_answers(com, 5, begin, end), 5);
    free_date(begin);
    free_date(end);
    printf("\t%sParams [50, 1/5/2013, 6/5/2013]%s\n", GREEN, RESET);
    begin = createDate(0,4,2013);
    end = createDate(5,4,2013);
    printAndDestroyLongList(most_voted_answers(com, 50, begin, end), 50);
    free_date(begin);
    free_date(end);

    printf("%sQUERY  7:%s Most answered questions\n",BLUE, RESET);
    printf("\t%sParams [10, 1/8/2014, 11/8/2014]%s\n", GREEN, RESET);
    begin = createDate(0,7,2014);
    end = createDate(10,7,2014);
    printAndDestroyLongList(most_answered_questions(com, 10, begin, end), 10);
    free_date(begin);
    free_date(end);
    printf("\t%sParams [100, 1/1/2012, 31/12/2012]%s\n", GREEN, RESET);
    begin = createDate(0,0,2012);
    end = createDate(30,11,2012);
    printAndDestroyLongList(most_answered_questions(com, 100, begin, end), 100);
    free_date(begin);
    free_date(end);

    printf("%sQUERY  8:%s Contains word\n",BLUE, RESET);
    printf("\t%sParams [kde, 10]%s\n", GREEN, RESET);
    printAndDestroyLongList(contains_word(com, "kde", 10), 10);
    printf("\t%sParams [glib, 10]%s\n", GREEN, RESET);
    printAndDestroyLongList(contains_word(com, "glib", 10), 10);

    printf("%sQUERY  9:%s Both participated\n",BLUE, RESET);
    printf("\t%sParams [87, 5691, 10]%s\n", GREEN, RESET);
    printAndDestroyLongList(both_participated(com, 87, 5691, 10), 10);
    printf("\t%sParams [253, 455, 5]%s\n", GREEN, RESET);
    printAndDestroyLongList(both_participated(com, 253, 455, 5), 5);

    printf("%sQUERY 10:%s Better answer\n",BLUE, RESET);
    printf("\t%sParams [30334]%s\n", GREEN, RESET);
    printf("Better answer: %ld\n", better_answer(com, 30334));
    printf("\t%sParams [5942]%s\n", GREEN, RESET);
    printf("Better answer: %ld\n", better_answer(com, 5942));

    printf("%sQUERY 11:%s Most used best rep\n",BLUE, RESET);
    printf("\t%sParams [5, 1/11/2013, 30/11/2013]%s\n", GREEN, RESET);
    begin = createDate(0,10,2013);
    end = createDate(29,10,2013);
    printAndDestroyLongList(most_used_best_rep(com, 5, begin, end), 5);
    free_date(begin);
    free_date(end);
    printf("\t%sParams [10, 1/1/2014, 31/12/2014]%s\n", GREEN, RESET);
    begin = createDate(0,0,2014);
    end = createDate(30,11,2014);
    printAndDestroyLongList(most_used_best_rep(com, 10, begin, end), 10);
    free_date(begin);
    free_date(end);

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
    if(!sP){
       printf(RED "(null)\n" RESET);
       return;
    }
    char* s = get_fst_str(sP);
    printf("%sfst:%s %s\n", YELLOW, RESET, s);
    free(s);
    s = get_snd_str(sP);
    printf("%ssnd:%s %s\n", YELLOW, RESET, s);
    free(s);
    free_str_pair(sP);
}

static void printAndDestroyLongPair(LONG_pair lP){
    if(!lP){
       printf(RED "(null)\n" RESET);
       return;
    }
    printf("%sfst:%s %ld\n", YELLOW, RESET, get_fst_long(lP));
    printf("%ssnd:%s %ld\n", YELLOW, RESET, get_snd_long(lP));
    free_long_pair(lP);
}

static void printAndDestroyLongList(LONG_list lL, int size){
    if(!lL){
       printf(RED "(null)\n" RESET);
       return;
    }
    if(size < 0) for(size = 0;get_list(lL,size) != 0; size++);
    printf("%s[",YELLOW);
    for(int i = 0; i < size; i++){
        printf(" %8ld", get_list(lL, i));
        if(i<size-1) printf(",");
    }
    printf("]%s\n",RESET);
    free_list(lL);
}

static void printAndDestroyUser(USER u){
    if(!u){
       printf(RED "(null)\n" RESET);
       return;
    }
    printf("bio: %s\n", get_bio(u));
    long *posts = get_10_latest_posts(u);
    for(int i=0; i<10; i++){
        printf("post[%d] -> %ld\n", i, posts[i]);
    }
    free(posts);
    free_user(u);
}
