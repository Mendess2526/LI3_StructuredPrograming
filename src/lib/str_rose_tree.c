#include "str_rose_tree.h"
#include "common.h"

#include <stdlib.h>
#include <glib.h>
#include <string.h>

typedef struct string_rose_tree_node * STR_RT_NODE;

struct string_rose_tree_node{
    char c;
    int count;
    STR_RT_NODE* nextNodes;
};

struct str_rose_tree{
    int biggestWord;
    STR_RT_NODE* trees;
};

typedef struct string_count_pair{
    char* word;
    int count;
}*STR_COUNT_PAIR;

#define CHAR2INDEX(c) ((int) (c)-' ')
#define NUM_NODES ('~'-' ' + 1)


static STR_COUNT_PAIR str_count_create(char* string, int count){
    STR_COUNT_PAIR scp = malloc(sizeof(struct string_count_pair));
    scp->word = mystrdup(string);
    scp->count = count;
    return scp;
}

static void str_count_destroy(gpointer p){
    STR_COUNT_PAIR scp = (STR_COUNT_PAIR) p;
    free(scp->word);
    free(scp);
}

static STR_RT_NODE str_tree_node_add(STR_RT_NODE node, char* c, int *depth){
    if(*c == '\0') return NULL;

    if(node == NULL){
        node = malloc(sizeof(struct string_rose_tree_node));
        node->c = *c;
        node->nextNodes = NULL;
        node->count = 0;
    }

    if(*(c+1) == '\0'){
        node->count++;
    }else{
        if(node->nextNodes == NULL)
            node->nextNodes = calloc(NUM_NODES, sizeof(STR_RT_NODE));
        node->nextNodes[CHAR2INDEX(*(c+1))] =
            str_tree_node_add(node->nextNodes[CHAR2INDEX(*(c+1))], c+1, depth);
    }
    *depth += 1;
    return node;
}

static void node_get_most_common_strings(STR_RT_NODE node, GSequence* seq, char* wordBag, int depth){
    if(node == NULL) return;
    wordBag[depth] = node->c;
    if(node->count > 0){
        g_sequence_prepend(seq, str_count_create(wordBag, node->count));
    }
    if(node->nextNodes != NULL){
        for(int i=0; i < NUM_NODES; i++){
            node_get_most_common_strings(node->nextNodes[i], seq, wordBag, depth+1);
        }
    }
    wordBag[depth] = '\0';
}

static void str_tree_node_destroy(STR_RT_NODE node){
    if(!node) return;
    for(int i=0; i < NUM_NODES; i++)
        if(node->nextNodes)
            str_tree_node_destroy(node->nextNodes[i]);
    free(node->nextNodes);
    free(node);
}

STR_ROSE_TREE str_rtree_create(){
    STR_ROSE_TREE tree = malloc(sizeof(struct str_rose_tree));
    tree->biggestWord = 1;
    tree->trees = calloc(NUM_NODES, sizeof(struct string_rose_tree_node));
    return tree;
}

void str_rtree_add(STR_ROSE_TREE tree, char* word){
    int idx = CHAR2INDEX(*word);
    int depth = 1;
    tree->trees[idx] = str_tree_node_add(tree->trees[idx], word, &depth);
    if(depth > tree->biggestWord) tree->biggestWord = depth;
}

gint cmpCount(gconstpointer a, gconstpointer b, gpointer user_data){
    return ((STR_COUNT_PAIR) b)->count - ((STR_COUNT_PAIR) a)->count;
}

char** str_rtree_get_most_common_strings(STR_ROSE_TREE tree, int N){
    GSequence* seq = g_sequence_new(str_count_destroy);
    for(int i=0; i < NUM_NODES; i++){
        char wordBag[tree->biggestWord];
        memset(wordBag, 0, sizeof(char)*tree->biggestWord);
        node_get_most_common_strings(tree->trees[i], seq, wordBag, 0);
    }
    g_sequence_sort(seq, cmpCount, NULL);
    GSequenceIter* it = g_sequence_get_begin_iter(seq);
    char** tags = malloc(sizeof(char*)*N);
    for(int i = 0; i < N && !g_sequence_iter_is_end(it); it = g_sequence_iter_next(it)){
        tags[i++] = mystrdup(((STR_COUNT_PAIR) g_sequence_get(it))->word);
    }
    g_sequence_free(seq);
    return tags;
}

void str_rtree_destroy(STR_ROSE_TREE tree){
    for(int i = 0; i < NUM_NODES; i++)
        str_tree_node_destroy(tree->trees[i]);
    free(tree->trees);
    free(tree);
}
