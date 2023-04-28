#include "binary_tree.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static inline void *
Malloc (size_t size)
{
	void *mem = malloc (size);
	if (mem == NULL) {
		fprintf (stderr, "malloc() failed");
		exit (EXIT_FAILURE);
	}
	return mem;
}

static const data_type EMPTY_BRANCH = -1;

static binary_tree_node *
real_binary_tree_new_DLR (const data_type *data_array, int *curr)
{
	binary_tree_node *tree;
	if (data_array[*curr] == EMPTY_BRANCH) {
		tree = NULL, ++*curr;
	} else {
		tree = Malloc (sizeof (binary_tree_node));
		tree->data = data_array[*curr], ++*curr;
		tree->lchild = real_binary_tree_new_DLR (data_array, curr);
		tree->rchild =  real_binary_tree_new_DLR (data_array, curr);
	}
	return tree;
}

binary_tree_node *
binary_tree_new_DLR (const data_type *data_array)
{
	int beg = 0;
	return real_binary_tree_new_DLR (data_array, &beg);
}

void
binary_tree_delete (binary_tree_node *tree)
{
	if (tree == NULL)
		return;
	else {
		binary_tree_delete (tree->lchild);
		binary_tree_delete (tree->rchild);
		free (tree);
	}
}

void
binary_tree_traverse_DLR (binary_tree_node *tree, void (*solve) (binary_tree_node *, void *), void *arg)
{
	if (tree == NULL)
		return;
	solve (tree, arg);
	binary_tree_traverse_DLR (tree->lchild, solve, arg);
	binary_tree_traverse_DLR (tree->rchild, solve, arg);
}

void
binary_tree_traverse_LDR (binary_tree_node *tree, void (*solve) (binary_tree_node *, void *), void *arg)
{
	if (tree == NULL)
		return;
	binary_tree_traverse_LDR (tree->lchild, solve, arg);
	solve (tree, arg);
	binary_tree_traverse_LDR (tree->rchild, solve, arg);
}

void
binary_tree_traverse_LRD (binary_tree_node *tree, void (*solve) (binary_tree_node *, void *), void *arg)
{
	if (tree == NULL)
		return;
	binary_tree_traverse_LRD (tree->lchild, solve, arg);
	binary_tree_traverse_LRD (tree->rchild, solve, arg);
	solve (tree, arg);
}

void
binary_tree_traverse_DLR_const (const binary_tree_node *tree,
                                void (*solve) (const binary_tree_node *, void *),
                                void *arg)
{
	binary_tree_traverse_DLR (
	    (binary_tree_node *) tree,
	    (void (*) (binary_tree_node *, void *)) solve,
	    arg
	);
}

void
binary_tree_traverse_LDR_const (const binary_tree_node *tree,
                                void (*solve) (const binary_tree_node *, void *),
                                void *arg)
{
	binary_tree_traverse_LDR (
	    (binary_tree_node *) tree,
	    (void (*) (binary_tree_node *, void *)) solve,
	    arg
	);
}

void
binary_tree_traverse_LRD_const (const binary_tree_node *tree,
                                void (*solve) (const binary_tree_node *, void *),
                                void *arg)
{
	binary_tree_traverse_LRD (
	    (binary_tree_node *) tree,
	    (void (*) (binary_tree_node *, void *)) solve,
	    arg
	);
}

bool
binary_tree_is_leaf_node (const binary_tree_node *node)
{
	if (node == NULL)
		return false;
	else
		return node->lchild == NULL && node->rchild == NULL;
}



static void inline
callback_INC_node_count (const binary_tree_node *tree, void *count)
{
	++* (int *) count;
}

int
binary_tree_get_node_count (const binary_tree_node *tree)
{
	int count = 0;
	binary_tree_traverse_DLR_const (tree, callback_INC_node_count, &count);
	return count;
}

static void inline
callback_INC_leaf_node_count (const binary_tree_node *tree, void *count)
{
	if (binary_tree_is_leaf_node (tree))
		++* (int *) count;
}

int
binary_tree_get_leaf_node_count (const binary_tree_node *tree)
{
	int count = 0;
	binary_tree_traverse_DLR_const (tree, callback_INC_leaf_node_count, &count);
	return count;
}

int
binary_tree_get_tree_depth (const binary_tree_node *tree)
{
	if (tree == NULL)
		return 0;
	else {
		int ldepth = binary_tree_get_tree_depth (tree->lchild);
		int rdepth = binary_tree_get_tree_depth (tree->rchild);
		if (ldepth > rdepth)
			return ldepth + 1;
		else
			return rdepth + 1;
	}
}

typedef
void (*binary_tree_traverse_func) (
    binary_tree_node *, void (*) (binary_tree_node *, void *), void *
);

typedef
void (*binary_tree_traverse_func_const) (
    const binary_tree_node *, void (*) (const binary_tree_node *, void *), void *
);

static binary_tree_traverse_func
get_traverse_func (binary_tree_traverse_order order)
{
	static binary_tree_traverse_func func_array[4] = {NULL};
	
	if (func_array[0] == NULL) {
		func_array[DLR] = binary_tree_traverse_DLR;
		func_array[LDR] = binary_tree_traverse_LDR;
		func_array[LRD] = binary_tree_traverse_LRD;
		func_array[LEVEL] = binary_tree_traverse_level;
	}
	
	return func_array[order];
}

static binary_tree_traverse_func_const
get_traverse_func_const (binary_tree_traverse_order order)
{
	static binary_tree_traverse_func_const func_array[4] = {NULL};
	
	if (func_array[0] == NULL) {
		func_array[DLR] = binary_tree_traverse_DLR_const;
		func_array[LDR] = binary_tree_traverse_LDR_const;
		func_array[LRD] = binary_tree_traverse_LRD_const;
		func_array[LEVEL] = binary_tree_traverse_level_const;
	}
	
	return func_array[order];
}

static void
callback_print_node_data (const binary_tree_node *tree, void *unused)
{
	printf ("%c ", tree->data);
}

void
binary_tree_print_data (const binary_tree_node *tree, binary_tree_traverse_order order)
{
	binary_tree_traverse_func_const func = get_traverse_func_const (order);
	func (tree, callback_print_node_data, NULL);
}

void
binary_tree_print_tree (const binary_tree_node *tree)
{
	if (tree == NULL)
		return;
	putchar (tree->data);
	if (tree->lchild != NULL) {
		putchar ('(');
		
		binary_tree_print_tree (tree->lchild);
		if (tree->rchild != NULL) {
			putchar (',');
			binary_tree_print_tree (tree->rchild);
		}
		
		putchar (')');
	} else if (tree->rchild != NULL) {
		putchar ('(');
		
		binary_tree_print_tree (tree->lchild);
		if (tree->rchild != NULL) {
			putchar (',');
			binary_tree_print_tree (tree->rchild);
		}
		
		putchar (')');
	}
}

binary_tree_node *
binary_tree_rebuild_from_DLR_and_LDR (const data_type *DLR_sequence, const data_type *LDR_sequence, size_t length)
{
	if (length == 0)
		return NULL;
	else {
		binary_tree_node *tree = Malloc (sizeof (binary_tree_node));
		char D = DLR_sequence[0];
		tree->data = D;
		
		char *D_in_LDR_sequence = strchr (LDR_sequence, D);
		size_t llength = D_in_LDR_sequence - LDR_sequence;
		size_t rlength = length - llength - 1;
		
		tree->lchild = binary_tree_rebuild_from_DLR_and_LDR (&DLR_sequence[1], LDR_sequence, llength);
		tree->rchild = binary_tree_rebuild_from_DLR_and_LDR (&DLR_sequence[1 + llength], D_in_LDR_sequence + 1, rlength);
		return tree;
	}
}

void
binary_tree_traverse_level (binary_tree_node *tree,
                            void (*solve) (binary_tree_node *, void *),
                            void *arg)
{
	const int QUEUE_MAX_SIZE = 4096;
	binary_tree_node *queue[QUEUE_MAX_SIZE];
	int front, rear, tmp;
	front = rear = 0;
	
#define ENQUEUE(node)\
	queue[rear] = node, rear = (rear +1) % QUEUE_MAX_SIZE
	
#define DEQUEUE()                           \
	( tmp = front,                          \
	  front = (front +1) % QUEUE_MAX_SIZE,  \
	  queue[tmp]                            \
	)
#define IS_QUEUE_EMPTY()\
	( rear == front )
#define IS_QUEUE_FULL()\
	( (rear +1 ) % QUEUE_MAX_SIZE == front )
	
	
	ENQUEUE (tree);
	for (; !IS_QUEUE_EMPTY() ;) {
		binary_tree_node *curr = DEQUEUE();
		solve (curr, arg);
		if (curr->lchild != NULL)
			ENQUEUE (curr->lchild);
		if (curr->rchild != NULL)
			ENQUEUE (curr->rchild);
	}
	
#undef ENQUEUE
#undef DEQUEUE
#undef IS_QUEUE_EMPTY
#undef IS_QUEUE_FULL
}

void
binary_tree_traverse_level_const (const binary_tree_node *tree,
                                  void (*solve) (const binary_tree_node *, void *),
                                  void *arg)
{
	binary_tree_traverse_level (
	    (binary_tree_node *) tree,
	    (void (*) (binary_tree_node *, void *)) solve,
	    arg
	);
}