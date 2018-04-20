#ifndef __STR_ROSE_TREE_H__
#define __STR_ROSE_TREE_H__

typedef struct str_rose_tree * STR_ROSE_TREE;

STR_ROSE_TREE str_rtree_create();

void str_rtree_add(STR_ROSE_TREE tree, char* word);

char** str_rtree_get_most_common_strings(STR_ROSE_TREE tree, int N);

void str_rtree_destroy(STR_ROSE_TREE tree);

#endif /* __STR_ROSE_TREE_H__ */
