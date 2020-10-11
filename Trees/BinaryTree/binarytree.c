#ifndef BINARY_TREE__C
#define BINART_TREE__C
#include <stdio.h>
#include <malloc.h>
#include "binarytree.h"

/**
 *
 *  Function new_binary_tree fails to create tree, if,
 *  either null is passed as cmp and or, there is no
 *  space left to allocate the space for the tree.
 *
 */


BinaryTree *new_binary_tree(bool (*cmp)(const void* left, const void* right)) {

	BinaryTree *tree = (BinaryTree*) malloc(sizeof(BinaryTree));

	//NULL value of cmp would lead to crashing, hence not allowed.

	if(!(tree && cmp)) return NULL;

	tree->root = NULL;
	tree->size = 0;
	tree->comparator = cmp;
	return tree;
}

BinaryNode *new_binary_node(void *data) {

	BinaryNode *node = (BinaryNode*) malloc(sizeof(BinaryNode*));
	if(!node) return NULL;

	node->data  = data;
	node->left  = NULL;
	node->right = NULL;
	return node;
}

BinaryNode* bst_insert(BinaryTree *tree, void *data, bool* success) {

	if(!tree) {
		*success = false;
		return NULL;
	}

	BinaryNode* node = new_binary_node(data);

	//Memory check.
	if(!node) {
		fputs(OUT_OF_MEM, stderr);
		*success = false;
		return NULL;
	}

	//Base case
	if(!tree->root) {
		tree->root = node;
		tree->size = tree->size + 1;
		*success = true;
		return node;
	}

	BinaryNode* curr_node = tree->root;
	int res;

	while(true) {
		res = tree->comparator(data, curr_node->data);
		if(!res) {
			*success = false; //Multiple occurences not allowed
			return NULL;
		}

		//Data to insert is less then curr_node
		if(res < 0) {
			if(curr_node->left != NULL) curr_node = curr_node->left;
			else break;
		}

		//Data to insert is greater then curr_node
		else {
			if(curr_node->right != NULL) curr_node = curr_node->right;
			else break;
		}
	}

	if(res < 0) curr_node->left = node;
	else curr_node->right = node;
	tree->size = tree->size + 1;
	*success = true;
	return node;
}

/*
int bst_get_inorder_pos(BinaryTree *tree, const void *data);
BinaryNode* 	bst_at(BinaryTree* tree, int pos);
void 	    	bst_remove(BinaryTree* tree, bool (*cmp)(const void *data));
int 	    	bst_size(BinaryTree *tree);
bool 	    	bst_isEmpty(BinaryTree *tree);
void 		clear(BinaryTree* tree);
bool	    	bst_contains(BinaryTree* tree, bool (*cmp)(const void *data));
*/


void bst_inorder_traversal_$$_(BinaryNode* node, void (*bst_print)(const void* data)) {
	if(node) {
		bst_inorder_traversal_$$_(node->left, bst_print);
		bst_print(node->data);
		bst_inorder_traversal_$$_(node->right, bst_print);
	}
}

void bst_inorder_traversal(BinaryTree* tree, void (*bst_print)(const void* data)) {
	if(!(tree && bst_print)) return;
	bst_inorder_traversal_$$_(tree->root, bst_print);
}

void bst_preorder_traversal_$$_(BinaryNode* node, void (*bst_print)(const void* data)) {
	if(node) {
		bst_print(node->data);
		bst_preorder_traversal_$$_(node->left, bst_print);
		bst_preorder_traversal_$$_(node->right, bst_print);
	}
}

void bst_preorder_traversal(BinaryTree* tree, void (*bst_print)(const void* data)) {
	if(!(tree && bst_print)) return;
	bst_preorder_traversal_$$_(tree->root, bst_print);
}

void bst_postorder_traversal_$$_(BinaryNode* node, void (*bst_print)(const void* data)) {
	if(node) {
		bst_postorder_traversal_$$_(node->left, bst_print);
		bst_postorder_traversal_$$_(node->right, bst_print);
		bst_print(node->data);
	}
}

void bst_postorder_traversal(BinaryTree* tree, void (*bst_print)(const void* data)) {
	if(!(tree && bst_print)) return;
	bst_postorder_traversal_$$_(tree->root, bst_print);
}

#endif
