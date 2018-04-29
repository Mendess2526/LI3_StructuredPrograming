#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "interface.h"
#include "pair.h"
#include "common.h"

//#define USING_DUMMY 1

#if USING_DUMMY
#include "community.h"
#endif

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
static void printAndDestroyLongList(LONG_list lL);
static void printAndDestroyUser(USER u);

#if USING_DUMMY
#define DUMMYU(i,rep) so_user_create(i,rep,(xmlChar*)"user",(xmlChar*)"user")
#define DUMMYQ(i,day, month, year, uid) community_add_question(com, question_create(i,dateTime_create(year,month-1,day-1,1,1,1,1),0,uid,(xmlChar*)"title",(xmlChar*)makeTags(day,month,year,uid,i),0,NULL));
#endif

char *makeTags(int day, int month, int year, int uid, int qid){
    char *tags = malloc(sizeof(char)*25);
    sprintf(tags,"<d%d><m%d><y%d><user%d><q%d>", day, month, year, uid, qid);
    return tags;
}

int main(int argc, const char **argv){
    char *folder;
    if(argc > 1)
        folder = makeDumpPath(argv[1]);
    else
        folder = makeDumpPath(NULL);

    TAD_community com = init();

#if USING_DUMMY
    printf(GREEN"Using dummy values\n"RESET);
#endif

#if !USING_DUMMY
    com = load(com,folder);
#endif

    free(folder);

#if USING_DUMMY
    int i = 1;
    community_add_user(com, DUMMYU(i,30)); i++;
    community_add_user(com, DUMMYU(i,25)); i++;
    community_add_user(com, DUMMYU(i,25)); i++;
    community_add_user(com, DUMMYU(i,15)); i++;
    community_add_user(com, DUMMYU(i,10)); i++;
    community_add_user(com, DUMMYU(i,05)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,01)); i++;
    community_add_user(com, DUMMYU(i,00)); i++;
    int worst = i-1;
    i = 1;
    //       d  m  a    u
    DUMMYQ(i, 1,11,2013,1    ); i++;
    DUMMYQ(i,15,11,2013,1    ); i++;
    DUMMYQ(i,31,10,2013,1    ); i++;
    DUMMYQ(i,14, 1,2013,1    ); i++;
    DUMMYQ(i,30,11,2014,1    ); i++;
    DUMMYQ(i,30,11,2013,worst); i++;

    for(int i = 0; i < 32; i++){
        char tag[5] = {0};
        sprintf(tag, "d%d", i);
        community_add_tag(com, i, xmlStrdup((xmlChar*) tag));
    }
    for(int i = 0; i < 13; i++){
        char tag[5] = {0};
        sprintf(tag, "m%d", i);
        community_add_tag(com, i+32, xmlStrdup((xmlChar*) tag));
    }
    for(int i = 0; i<3000; i++){
        char tag[5] = {0};
        sprintf(tag, "y%d", i);
        community_add_tag(com, i+32+13, xmlStrdup((xmlChar*) tag));
    }
    for(int i = 0, tagId = 1; i<20; i++, tagId++){
        char tag[7] = {0};
        sprintf(tag, "user%d", i);
        community_add_tag(com, tagId+32+13+3000, xmlStrdup((xmlChar*) tag));
        sprintf(tag, "q%d", i);
        tagId++;
        community_add_tag(com, tagId+32+13+3000, xmlStrdup((xmlChar*) tag));
    }
#endif

    Date begin, end;

    printf("%sQUERY  1:%s Info from Post\n" ,BLUE, RESET);
    printf("%sParams [801049]%s\n", GREEN, RESET);
    printAndDestroyStrPair(info_from_post(com, 801049));
    printf("%sParams [796430]%s\n", GREEN, RESET);
    printAndDestroyStrPair(info_from_post(com, 796430));

    printf("%sQUERY  2:%s Top most active\n",BLUE, RESET);
    printf("\t%sParams [10]%s\n", GREEN, RESET);
    printAndDestroyLongList(top_most_active(com, 10));
    printf("\t%sParams [100]%s\n", GREEN, RESET);
    printAndDestroyLongList(top_most_active(com, 100));

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
    printAndDestroyLongList(questions_with_tag(com, "package-management", begin, end));
    free_date(begin);
    free_date(end);
    printf("\t%sParams [nautilus, 1/1/2014, 31/1/2014]%s\n", GREEN, RESET);
    begin = createDate(0,0,2014);
    end = createDate(30,0,2014);
    printAndDestroyLongList(questions_with_tag(com, "nautilus", begin, end));
    free_date(begin);
    free_date(end);

    printf("%sQUERY  5:%s Get user info\n",BLUE, RESET);
    printf("\t%sParams [15811]%s\n", GREEN, RESET);
    printAndDestroyUser(get_user_info(com, 15811));
    printf("\t%sParams [449]%s\n", GREEN, RESET);
    printAndDestroyUser(get_user_info(com, 449));

    printf("%sQUERY  6:%s Most voted answer",BLUE, RESET);
    printf("\t%sParams [5, 1/11/2015, 30/11/2015]%s\n", GREEN, RESET);
    begin = createDate(0,10,2015);
    end = createDate(29,10,2015);
    printAndDestroyLongList(most_voted_answers(com, 5, begin, end));
    free_date(begin);
    free_date(end);
    printf("\t%sParams [50, 1/5/2013, 6/5/2013]%s\n", GREEN, RESET);
    begin = createDate(0,4,2013);
    end = createDate(5,4,2013);
    printAndDestroyLongList(most_voted_answers(com, 50, begin, end));
    free_date(begin);
    free_date(end);

    printf("%sQUERY  7:%s Most answered questions\n",BLUE, RESET);
    printf("\t%sParams [10, 1/8/2014, 11/8/2014]%s\n", GREEN, RESET);
    begin = createDate(0,7,2014);
    end = createDate(10,7,2014);
    printAndDestroyLongList(most_answered_questions(com, 10, begin, end));
    free_date(begin);
    free_date(end);
    printf("\t%sParams [100, 1/1/2012, 31/12/2012]%s\n", GREEN, RESET);
    begin = createDate(0,0,2012);
    end = createDate(30,11,2012);
    printAndDestroyLongList(most_answered_questions(com, 100, begin, end));
    free_date(begin);
    free_date(end);

    printf("%sQUERY  8:%s Contains word\n",BLUE, RESET);
    printf("\t%sParams [kde, 10]%s\n", GREEN, RESET);
    printAndDestroyLongList(contains_word(com, "kde", 10));
    printf("\t%sParams [glib, 10]%s\n", GREEN, RESET);
    printAndDestroyLongList(contains_word(com, "glib", 10));

    printf("%sQUERY  9:%s Both participated\n",BLUE, RESET);
    printf("\t%sParams [87, 5691, 10]%s\n", GREEN, RESET);
    printAndDestroyLongList(both_participated(com, 87, 5691, 10));
    printf("\t%sParams [253, 455, 5]%s\n", GREEN, RESET);
    printAndDestroyLongList(both_participated(com, 253, 455, 5));

    printf("%sQUERY 10:%s Better answer\n",BLUE, RESET);
    printf("\t%sParams [30334]%s\n", GREEN, RESET);
    printf("Better answer: %ld\n", better_answer(com, 30334));
    printf("\t%sParams [5942]%s\n", GREEN, RESET);
    printf("Better answer: %ld\n", better_answer(com, 5942));

    printf("%sQUERY 11:%s Most used best rep\n",BLUE, RESET);
    printf("\t%sParams [5, 1/11/2013, 30/11/2013]%s\n", GREEN, RESET);
    begin = createDate(0,10,2013);
    end = createDate(29,10,2013);
    printAndDestroyLongList(most_used_best_rep(com, 5, begin, end));
    free_date(begin);
    free_date(end);
    printf("\t%sParams [10, 1/1/2014, 31/12/2014]%s\n", GREEN, RESET);
    begin = createDate(0,0,2014);
    end = createDate(30,11,2014);
    printAndDestroyLongList(most_used_best_rep(com, 10, begin, end));
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

static void printAndDestroyLongList(LONG_list lL){
    if(!lL){
       printf(RED "(null)\n" RESET);
       return;
    }
    printf("%s[",YELLOW);
    for(int i = 0; get_list(lL, i); i++){
        printf(" %6ld", get_list(lL, i));
        if(get_list(lL, i+1) != 0){
            printf(",");
            if(((i+1) % 10) == 0) printf("\n ");
        }
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
