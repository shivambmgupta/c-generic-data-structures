#include <stdio.h>
#include "singlylinkedlist.c"

int main() {
	SinglyLinkedList *list = new_list();
	char* str = "hii";
	push_back(list, str);
	Node* node = list->head;
	while(node != NULL) {
		char *str = node->data;
		printf("%s\n", str);
		printf("%u\n", list->head);
		printf("%u\n", list->end);
		node = node->next;
	}
	printf("Before popping\n");
	erase(list, str);
	printf("After popping\n");
	node = list->head;
	while(node != NULL) {
		char *str = node->data;
		printf("%s\n", str);
		printf("%u\n", list->head);
		printf("%u\n", list->end);
		node = node->next;
	}
	return 0;
}