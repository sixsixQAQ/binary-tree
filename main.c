#include <stdio.h>
#include <string.h>
#include "binary_tree.h"


void
print_all (binary_tree_node *tree)
{
	printf ("先序遍历: "), binary_tree_print_data (tree, DLR), putchar ('\n');
	printf ("中序遍历: "), binary_tree_print_data (tree, LDR), putchar ('\n');
	printf ("后序遍历: "), binary_tree_print_data (tree, LRD), putchar ('\n');
	printf ("层序遍历: "), binary_tree_print_data (tree, LEVEL), putchar ('\n');
	
	printf ("打印树： "), binary_tree_print_tree (tree), putchar ('\n');
	
	printf ("结点数：%d\n", binary_tree_get_node_count (tree));
	printf ("叶子结点数：%d\n", binary_tree_get_leaf_node_count (tree));
	printf ("树深：%d\n", binary_tree_get_tree_depth (tree));
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
	
	{
		puts ("--------------重建树--------------：");
		char *DLR_sequence = "ABCDEFGHI";
		char *LDR_sequence = "DECBFAHGI";
		
		binary_tree_node *tree = binary_tree_rebuild_from_DLR_and_LDR (
		                             DLR_sequence, LDR_sequence, strlen (DLR_sequence)
		                         );
		                         
		print_all (tree);
		
		binary_tree_delete (tree);
	}
	puts ("----------------------------------------------------------");
	
	
	
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
	{
		puts ("--------------重建树--------------：");
		char *DLR_sequence = "ABDHECFIJG";
		char *LDR_sequence = "DHBEAIFJCG";
		
		binary_tree_node *tree = binary_tree_rebuild_from_DLR_and_LDR (
		                             DLR_sequence, LDR_sequence, strlen (DLR_sequence)
		                         );
		                         
		print_all (tree);
		
		binary_tree_delete (tree);
	}
}
