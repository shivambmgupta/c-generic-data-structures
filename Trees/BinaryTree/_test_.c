#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "binarytree.c"

int cmp(const void* left, const void* right) {
	int l = *(int*)left;
	int r = *(int*)right;
	return l - r;
}

void bst_print(const void* data) {
	printf("%d ", *(int*)data);
}

int main() {
	BinaryTree *integer_tree = new_binary_tree(cmp);
	if(!integer_tree) {
		fputs(OUT_OF_MEM, stderr);
		return 0;
	}
	bool success;
	for(int i = 0; i < 5; ++i) {
		int *j = (int*) malloc(sizeof(int));
		memcpy(j, &i, sizeof(int));
		printf("Inserting: %d\n", *j);
		bst_insert(integer_tree, j, &success);
	}

	for(int i = 1; i < 5; ++i) {
		int *j = (int*) malloc(sizeof(int));
		*j = (i * -1);
		bst_insert(integer_tree, j, &success);
	}

	printf("\nInorder Traversing...\n");
	bst_inorder_traversal(integer_tree, bst_print);

	printf("\n\nPreorder Traversing...\n");
	bst_preorder_traversal(integer_tree, bst_print);

	printf("\n\nPostorder Traversing...\n");
	bst_postorder_traversal(integer_tree, bst_print);

	return 0;
}
