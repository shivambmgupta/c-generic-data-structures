#ifndef BINARY_TREE__H
#define BINARY_TREE__H
#include <stdio.h>

#define bool int
#define true  1
#define false 0

#define OUT_OF_MEM "Out of memory\n"

typedef struct __$$__bst_node {
	void* data;
	struct __$$__bst_node *left;
	struct __$$__bst_node *right;
} BinaryNode;

typedef struct __$$__bs_tree {
	int size;
	BinaryNode* root;
	bool (*comparator)(const void* left, const void* right);
} BinaryTree;

BinaryTree*	new_binary_tree(bool (*comparator)(const void* left, const void* right));
BinaryNode* 	new_binary_node(void *data);
BinaryNode* 	bst_insert(BinaryTree *tree, void *data, bool* success);
int 	    	bst_get_inorder_pos(BinaryTree *tree, const void *data);
BinaryNode* 	bst_at(BinaryTree* tree, int pos);
void 	    	bst_remove(BinaryTree* tree, bool (*cmp)(const void *data));
int 	    	bst_size(BinaryTree *tree);
bool 	    	bst_isEmpty(BinaryTree *tree);
void 		clear(BinaryTree* tree);
bool	    	bst_contains(BinaryTree* tree, bool (*cmp)(const void *data));
void		bst_inorder_traversal(BinaryTree* tree, void (*bst_print)(const void* data));
void		bst_preorder_traversal(BinaryTree* tree, void (*bst_print)(const void* data));
void		bst_postorder_traversal(BinaryTree* tree, void (*bst_print)(const void* data));

#endif

