#include <stdio.h>
#include <string.h>
#include "binary_tree.h"


void
print_all (binary_tree_node *tree)
{
	printf ("preorder traverse: \t"), binary_tree_print_data (tree, DLR), putchar ('\n');
	printf ("inorder traverse: \t"), binary_tree_print_data (tree, LDR), putchar ('\n');
	printf ("postorder traverse: \t"), binary_tree_print_data (tree, LRD), putchar ('\n');
	printf ("level-order traverse: \t"), binary_tree_print_data (tree, LEVEL), putchar ('\n');
	
	printf ("print tree： \t\t"), binary_tree_print_tree (tree), putchar ('\n');
	
	printf ("node count：\t\t%d\n", binary_tree_get_node_count (tree));
	printf ("leaf node count：\t%d\n", binary_tree_get_leaf_node_count (tree));
	printf ("tree depth：\t\t%d\n", binary_tree_get_tree_depth (tree));
}

int
main (void)
{

	/**
	 * Demo
	 *                  A
	 *                /   \
	 *              B      G
	 *            /  \    / \
	 *          C     F  H   I
	 *        /
	 *      D
	 *       \
	 *        E
	*/
	
	{
		char DLR_data[] = {'A', 'B', 'C', 'D', -1, 'E', -1, -1, -1, 'F', -1, -1, 'G', 'H', -1, -1, 'I', -1, -1};
		binary_tree_node *tree = binary_tree_new_DLR (DLR_data);
		
		print_all (tree);
		
		binary_tree_delete (tree);
	}
	
	puts("-------------------------------------------------------");
	
	/**
	 * Demo 2
	 *                  A
	 *                /   \
	 *              B      C
	 *            /  \    / \
	 *          D     E  F   G
	 *           \      / \
	 *            H    I   J
	*/
	{
		char DLR_data[] = {'A', 'B', 'D', -1, 'H', -1, -1, 'E', -1, -1, 'C', 'F', 'I', -1, -1, 'J', -1, -1, 'G', -1, -1};
		binary_tree_node *tree = binary_tree_new_DLR (DLR_data);
		print_all (tree);
		binary_tree_delete (tree);
	}
}
