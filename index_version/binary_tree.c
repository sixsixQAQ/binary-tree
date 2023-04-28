#include "binary_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static void *
Malloc (size_t size)
{
	void *mem = malloc (size);
	if (mem == NULL) {
		fprintf (stderr, "malloc() failed");
		exit (EXIT_FAILURE);
	}
	return mem;
}

static int
real_binary_tree_new (binary_tree_node *tree, const char *data_array, int *tree_i, int *data_i)
{
	if (data_array[*data_i] == -1) {
		++*data_i;
		return -1;
	} else {
		const int curr = *tree_i;
		tree[curr].data = data_array[*data_i], ++*tree_i, ++*data_i;
		tree[curr].lchild = real_binary_tree_new (tree, data_array, tree_i, data_i);
		tree[curr].rchild = real_binary_tree_new (tree, data_array, tree_i, data_i);
		return curr;
	}
}

binary_tree_node *
binary_tree_new_DLR (const char *data_array)
{
	binary_tree_node *tree = Malloc (sizeof (binary_tree_node) * strlen (data_array));
	int tree_i = 0;
	int data_i = 0;
	real_binary_tree_new (tree, data_array, &tree_i, &data_i);
	return tree;
}

void
binary_tree_delete (binary_tree_node *tree)
{
	free (tree);
}


static void
real_binary_tree_traverse_DLR (binary_tree_node *tree,
                               int curr,
                               void (*solve) (binary_tree_node *, void *),
                               void *arg)
{
	if (curr == -1)
		return;
	solve (&tree[curr], arg);
	real_binary_tree_traverse_DLR (tree, tree[curr].lchild, solve, arg);
	real_binary_tree_traverse_DLR (tree, tree[curr].rchild, solve, arg);
}

static void
real_binary_tree_traverse_LDR (binary_tree_node *tree,
                               int curr,
                               void (*solve) (binary_tree_node *, void *),
                               void *arg)
{
	if (curr == -1)
		return;
	real_binary_tree_traverse_LDR (tree, tree[curr].lchild, solve, arg);
	solve (&tree[curr], arg);
	real_binary_tree_traverse_LDR (tree, tree[curr].rchild, solve, arg);
}

static void
real_binary_tree_traverse_LRD (binary_tree_node *tree,
                               int curr,
                               void (*solve) (binary_tree_node *, void *),
                               void *arg)
{
	if (curr == -1)
		return;
	real_binary_tree_traverse_LRD (tree, tree[curr].lchild, solve, arg);
	real_binary_tree_traverse_LRD (tree, tree[curr].rchild, solve, arg);
	solve (&tree[curr], arg);
}

void
binary_tree_traverse_DLR (binary_tree_node *tree,
                          void (*solve) (binary_tree_node *, void *),
                          void *arg)
{
	real_binary_tree_traverse_DLR (tree, 0, solve, arg);
}

void
binary_tree_traverse_LDR (binary_tree_node *tree,
                          void (*solve) (binary_tree_node *, void *),
                          void *arg)
{
	real_binary_tree_traverse_LDR (tree, 0, solve, arg);
}

void
binary_tree_traverse_LRD (binary_tree_node *tree,
                          void (*solve) (binary_tree_node *, void *),
                          void *arg)
{
	real_binary_tree_traverse_LRD (tree, 0, solve, arg);
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
	
#define DEQUEUE()                               \
	( tmp = front,                              \
	  front = (front + 1 ) % QUEUE_MAX_SIZE,    \
	  queue[tmp]                                \
	)
#define IS_QUEUE_EMPTY()\
	( rear == front )
#define IS_QUEUE_FULL()\
	( (rear +1 ) % QUEUE_MAX_SIZE == front )
	
	
	ENQUEUE (tree);
	for (; !IS_QUEUE_EMPTY() ;) {
		binary_tree_node *curr = DEQUEUE();
		solve (curr, arg);
		if (curr->lchild != -1)
			ENQUEUE (&tree[curr->lchild]);
		if (curr->rchild != -1)
			ENQUEUE (&tree[curr->rchild]);
	}
	
#undef ENQUEUE
#undef DEQUEUE
#undef IS_QUEUE_EMPTY
#undef IS_QUEUE_FULL
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

bool
binary_tree_is_leaf_node (const binary_tree_node *node)
{
	return node->lchild == -1 && node->rchild == -1;
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

static int
real_binary_tree_get_tree_depth (const binary_tree_node *tree, int curr)
{
	if (curr == -1)
		return 0;
	else {
		int ldepth = real_binary_tree_get_tree_depth (tree, tree[curr].lchild);
		int rdepth = real_binary_tree_get_tree_depth (tree, tree[curr].rchild);
		if (ldepth > rdepth)
			return ldepth + 1;
		else
			return rdepth + 1;
	}
}

int
binary_tree_get_tree_depth (const binary_tree_node *tree)
{
	return real_binary_tree_get_tree_depth (tree, 0);
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

static void
real_binary_tree_print_tree (const binary_tree_node *tree, int curr)
{
	if (curr == -1)
		return;
	putchar (tree[curr].data);
	if (tree[curr].lchild != -1) {
		putchar ('(');
		
		real_binary_tree_print_tree (tree, tree[curr].lchild);
		if (tree[curr].rchild != -1) {
			putchar (',');
			real_binary_tree_print_tree (tree, tree[curr].rchild);
		}
		
		putchar (')');
	} else if (tree[curr].rchild != -1) {
		putchar ('(');
		
		real_binary_tree_print_tree (tree, tree[curr].lchild);
		if (tree[curr].rchild != -1) {
			putchar (',');
			real_binary_tree_print_tree (tree, tree[curr].rchild);
		}
		
		putchar (')');
	}
}

void
binary_tree_print_tree (const binary_tree_node *tree)
{
	real_binary_tree_print_tree (tree, 0);
}