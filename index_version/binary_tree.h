/**
 *
 * 二叉树数组版本实现。
 * 1. 不提供树重建
 * 2. 实现均建立在树至少有一个结点的基础上，至少一个根结点。
 *
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct binary_tree_node {
	char data;
	int lchild, rchild;
} binary_tree_node;

binary_tree_node *binary_tree_new_DLR (const char *data_array);

void binary_tree_delete (binary_tree_node *tree);

void binary_tree_traverse_DLR (binary_tree_node *tree,
                               void (*solve) (binary_tree_node *, void *),
                               void *arg);
void binary_tree_traverse_LDR (binary_tree_node *tree,
                               void (*solve) (binary_tree_node *, void *),
                               void *arg);
void binary_tree_traverse_LRD (binary_tree_node *tree,
                               void (*solve) (binary_tree_node *, void *),
                               void *arg);
void binary_tree_traverse_level (binary_tree_node *tree,
                                 void (*solve) (binary_tree_node *, void *),
                                 void *arg);

void binary_tree_traverse_DLR_const (const binary_tree_node *tree,
                                     void (*solve) (const binary_tree_node *, void *),
                                     void *arg);
void binary_tree_traverse_LDR_const (const binary_tree_node *tree,
                                     void (*solve) (const binary_tree_node *, void *),
                                     void *arg);
void binary_tree_traverse_LRD_const (const binary_tree_node *tree,
                                     void (*solve) (const binary_tree_node *, void *),
                                     void *arg);
void binary_tree_traverse_level_const (const binary_tree_node *tree,
                                       void (*solve) (const binary_tree_node *, void *),
                                       void *arg);
bool binary_tree_is_leaf_node (const binary_tree_node *node);

int binary_tree_get_node_count (const binary_tree_node *tree);

int binary_tree_get_leaf_node_count (const binary_tree_node *tree);

int binary_tree_get_tree_depth (const binary_tree_node *tree);

typedef enum binary_tree_traverse_order {
	DLR, LDR, LRD, LEVEL
} binary_tree_traverse_order;

void binary_tree_print_tree (const binary_tree_node *tree);
void binary_tree_print_data (const binary_tree_node *tree, binary_tree_traverse_order order);

#endif // BINARY_TREE_H