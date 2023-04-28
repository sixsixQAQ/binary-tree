#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef char data_type;

typedef struct binary_tree_node binary_tree_node;
struct binary_tree_node {
	data_type data;
	binary_tree_node *lchild, *rchild;
};

binary_tree_node *binary_tree_new_DLR (const data_type *data_array);

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

binary_tree_node *binary_tree_rebuild_from_DLR_and_LDR (
    const data_type *DLR_sequence,
    const data_type *LDR_sequence,
    size_t length
);



#endif // BINARY_TREE_H