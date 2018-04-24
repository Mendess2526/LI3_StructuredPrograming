#ifndef __STR_ROSE_TREE_H__
#define __STR_ROSE_TREE_H__
/**
 * @file
 * \brief Módulo que define uma arvore n-aria para contar strings
 */

/** Tipo abstráto de àrvore n-aria para contar strings */
typedef struct str_rose_tree * STR_ROSE_TREE;

/**
 * Cria uma instância de uma arvora n-aria
 * @returns Um instância vazia da arvore
 */
STR_ROSE_TREE str_rtree_create();

/**
 * Adciona uma string à àrvore
 * @param tree A instância onde adicionar
 * @param word Palavra a adicionar
 */
void str_rtree_add(STR_ROSE_TREE tree, char* word);

/**
 * Computa a lista das \p N palavras mais comuns
 * @param tree A instância onde adicionar
 * @param N O tamanho da lista a criar
 */
char** str_rtree_get_most_common_strings(STR_ROSE_TREE tree, int N);

/**
 * Liberta a memória ocupada por uma instancia da arvore
 * @param tree A instância onde adicionar
 */
void str_rtree_destroy(STR_ROSE_TREE tree);

#endif /* __STR_ROSE_TREE_H__ */
