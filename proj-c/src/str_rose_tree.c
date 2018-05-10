#include "str_rose_tree.h"
#include "common.h"

#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <stdio.h>

typedef struct string_count_pair{
    char* word;
    int count;
}* STR_COUNT_PAIR;

typedef struct string_rose_tree_node* STR_RT_NODE;

struct string_rose_tree_node{
    char c;
    int count;
    STR_RT_NODE* nextNodes;
};

struct str_rose_tree{
    int biggestWord;
    STR_RT_NODE* trees;
};

/** Converte um char no índice correto. */
#define CHAR2INDEX(c) ((int) (c)-' ')
/** Define o número de nós do array de nós. */
#define NUM_NODES ('~'-' ' + 1)


/**
 * Cria uma instância de STR_COUNT_PAIR.
 * @param string String.
 * @param count Contagem.
 * @returns Instância de STR_COUTN_PAIR.
 */
static STR_COUNT_PAIR str_count_create(char* string, int count);

/**
 * Liberta a memória de um STR_COUNT_PAIR.
 * @param p Instância a libertar.
 */
static void str_count_destroy(gpointer p);

/**
 * Conta uma string a partir de um nó.
 * @param node Nó a partir do qual contar.
 * @param c String a contar.
 * @param depth Profundidade que foi preenchida.
 * @returns O nó que foi passado como argumento, caso seja NULL
 *          é retornado um nó inicializado.
 */
static STR_RT_NODE node_add(STR_RT_NODE node, char* c, int* depth);

/**
 * Coleciona as strings com contagem superior a 0, associadas a essa mesma contagem,
 * numa GSequence.
 * @param node Nó a partir do qual procurar.
 * @param seq GSequence onde inserir.
 * @param wordBag String onde colocar a string encontrada neste nó.
 * @param depth Profundidade deste nó.
 */
static void node_get_strings(STR_RT_NODE node,
                             GSequence* seq,
                             char* wordBag,
                             int depth);

/**
 * Liberta a memória ocupada por um nó e sub-nós da árvore.
 * @param node Nó a libertar.
 */
static void node_destroy(STR_RT_NODE node);

/**
 * Função que compara as contagens de duas strings.
 * @param a Par a.
 * @param b Par b.
 * @param user_data (ignored).
 * @returns Um número positivo se a contagem de b for maior que de a, um número
 *          negativo se a contagem de a for maior que a de b, 0 caso sejam iguais.
 */
static gint cmpCount(gconstpointer a, gconstpointer b, gpointer user_data);

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

static STR_RT_NODE node_add(STR_RT_NODE node, char* c, int* depth){
    if(*c == '\0') return NULL;

    if(node == NULL){
        node = malloc(sizeof(struct string_rose_tree_node));
        node->c = *c;
        node->nextNodes = NULL;
        node->count = 0;
    }

    if(*(c + 1) == '\0'){
        node->count++;
    }else{
        if(node->nextNodes == NULL)
            node->nextNodes = calloc(NUM_NODES, sizeof(STR_RT_NODE));
        node->nextNodes[CHAR2INDEX(*(c + 1))] =
                node_add(node->nextNodes[CHAR2INDEX(*(c + 1))], c + 1, depth);
    }
    *depth += 1;
    return node;
}

static void node_get_strings(STR_RT_NODE node,
                             GSequence* seq,
                             char* wordBag,
                             int depth){
    if(node == NULL) return;
    wordBag[depth] = node->c;
    if(node->count > 0){
        g_sequence_prepend(seq, str_count_create(wordBag, node->count));
    }
    if(node->nextNodes != NULL){
        for(int i = NUM_NODES - 1; i >= 0; i--){
            node_get_strings(node->nextNodes[i], seq, wordBag, depth + 1);
        }
    }
    wordBag[depth] = '\0';
}

static void node_destroy(STR_RT_NODE node){
    if(!node) return;
    for(int i = 0; i < NUM_NODES; i++)
        if(node->nextNodes)
            node_destroy(node->nextNodes[i]);
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
    tree->trees[idx] = node_add(tree->trees[idx], word, &depth);
    if(depth > tree->biggestWord) tree->biggestWord = depth;
}

static gint cmpCount(gconstpointer a, gconstpointer b, gpointer user_data){
    (void) user_data;
    return ((STR_COUNT_PAIR) b)->count - ((STR_COUNT_PAIR) a)->count;
}

char** str_rtree_get_most_common_strings(STR_ROSE_TREE tree, int N){
    GSequence* seq = g_sequence_new(str_count_destroy);
    for(int i = NUM_NODES - 1; i >= 0; i--){
        char wordBag[tree->biggestWord];
        memset(wordBag, 0, sizeof(char) * tree->biggestWord);
        node_get_strings(tree->trees[i], seq, wordBag, 0);
    }
    g_sequence_sort(seq, cmpCount, NULL);
    GSequenceIter* it = g_sequence_get_begin_iter(seq);
    char** tags = malloc(sizeof(char*) * (N + 1));
    int i;
    for(i = 0;
        i < N && !g_sequence_iter_is_end(it); it = g_sequence_iter_next(it)){
        STR_COUNT_PAIR scp = (STR_COUNT_PAIR) g_sequence_get(it);
        tags[i++] = mystrdup(scp->word);
    }
    tags[i] = NULL;
    g_sequence_free(seq);
    return tags;
}

void str_rtree_destroy(STR_ROSE_TREE tree){
    for(int i = 0; i < NUM_NODES; i++)
        node_destroy(tree->trees[i]);
    free(tree->trees);
    free(tree);
}
