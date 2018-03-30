#include <date.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "pair.h"
#include "community.h"

int main(int argc, const char **argv){
    char dumps[] = "/home/mendes/dump_exemplo/";
    char folder[26+30];
    if(argc < 2){
        sprintf(folder,"%s%s",dumps,"askubuntu/");
    }else{
        if(strlen(*(argv+1)) >= 30){
            printf("Folder name too big. Max 30 char\n");
            return -1;
        }
        sprintf(folder,"%s%s",dumps,*(argv+1));
    }
    TAD_community com = init();
    com = load(com,folder);
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
