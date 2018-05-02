#ifndef __STR_ROSE_TREE_H__
#define __STR_ROSE_TREE_H__

 /**
 * @file
 * \brief Módulo que define uma árvore n-ária para contar strings.
 */

 /** Tipo abstrato de árvore n-ária para contar strings. */
typedef struct str_rose_tree * STR_ROSE_TREE;

 /**
 * Cria uma instância de uma árvore n-ária.
 * @returns Uma instância vazia da árvore.
 */
STR_ROSE_TREE str_rtree_create();

 /**
 * Adciona uma string à árvore.
 * @param tree A instância onde adicionar.
 * @param word Palavra a adicionar.
 */
void str_rtree_add(STR_ROSE_TREE tree, char* word);

 /**
 * Computa a lista das N palavras mais comuns.
 * @param tree Uma instância da árvore.
 * @param N O tamanho da lista a criar.
 */
char** str_rtree_get_most_common_strings(STR_ROSE_TREE tree, int N);

 /**
 * Liberta a memória ocupada pela instância da árvore.
 * @param tree Uma instância da árvore.
 */
void str_rtree_destroy(STR_ROSE_TREE tree);

#endif /* __STR_ROSE_TREE_H__ */
