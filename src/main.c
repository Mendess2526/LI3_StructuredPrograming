#include <date.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "pair.h"
#include "community.h"

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
char* makeDumpPath(const char* folder_name){
    char *home = getenv("HOME");
    char *dumps = "/dump_exemplo/";
    char *folder = NULL;
    if(!folder_name) folder = strdup("askubuntu/");
    else folder = strdup(folder_name);
    size_t len = strlen(home) + strlen(dumps) + strlen(folder);
    char* path = (char*) malloc(sizeof(char)*len);
    sprintf(path,"%s%s%s", home, dumps, folder);
    free(folder);
    return path;
}

int main(int argc, const char **argv){
    argc = 0;
    char *folder = makeDumpPath(argv[1]);
    TAD_community com = init();
    com = load(com,folder);
    free(folder);
    /*
    STR_pair strPair = info_from_post(com,1);
    if(strPair) free_str_pair(strPair);
    top_most_active(com, 1);
    total_posts(com,NULL,NULL);
    questions_with_tag(com,NULL,NULL,NULL);
    get_user_info(com,1);
    most_voted_answers(com,1,NULL,NULL);
    most_answered_questions(com,1,NULL,NULL);
    contains_word(com,NULL,1);
    both_participated(com,1,2,3);
    better_answer(com,1);
    most_used_best_rep(com,1,NULL,NULL);
    */
    clean(com);
}
