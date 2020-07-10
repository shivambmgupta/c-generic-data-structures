#include <stdio.h>
#include <malloc.h>
#include "singlylinkedlist.h"

SinglyLinkedList* this;

Node* push_back(SinglyLinkedList* list, void *data) {	

	Node* node = (Node*) malloc(sizeof(Node));
	if(node == NULL) {
		printf("Out of Memory.\n");
		return NULL;
	}
	node->data = data;
	node->next = NULL;
	if(list->end == NULL) {
		list->head = node;
		list->end  = node;
		list->size = list->size + 1;
		return node;
	}

	list->end->next = node;
	list->end = node;
	list->size = list->size + 1;
	return node;
}

Node* push_front(SinglyLinkedList* list, void *data) {

	Node *node = (Node*) malloc(sizeof(Node));
	if(node == NULL) return NULL; //Out of Memory

	node->data = data;
	if( list->head == NULL ) {
		node->next = NULL;
		list->end = node;
	}
	else node->next = list->head;

	list->head = node;
	list->size = list->size + 1;
	return node;	
}

Node* insert(SinglyLinkedList* list, void *data, int pos) {

	if(pos >= list->size) return push_back(list, data);
	if(pos <= 0) 	      return push_front(list, data);
	
	Node *node = (Node*) malloc(sizeof(Node));
	if(node == NULL)  return NULL; //Out of Memory

	node->data = data;

	int i = 1;
	Node* curr_node = list->head;
	while( i < pos ) {
		curr_node = curr_node->next;
		++i;
	}
	node->next = curr_node->next;
	curr_node->next = node;
	list->size = list->size + 1;
	return node;		

}

void pop_back(SinglyLinkedList *list) {

	if(list->size == 0) return;

	if(list->size == 1) {
		//list->head = list->end
		free(list->end);
		list->head = NULL;
		list->end  = NULL;
		list->size = 0;
		return;
	}

	//list->head != list->end

	Node* curr_node = list->head;
	while(curr_node->next != list->end) curr_node = curr_node->next;
	curr_node->next = NULL;
	free(list->end);
	list->end = curr_node;
	list->size = list->size - 1;
}

void pop_front(SinglyLinkedList *list) {

	if(list->size == 0) return;

	if(list->size == 1) {
		//list->head = list->end
		free(list->end);
		list->head = NULL;
		list->end  = NULL;
		list->size = 0;
		return;
	}

	//list->head != list->end

	Node* temp = list->head;
	list->head = temp->next;
	list->size = list->size - 1;
	free(temp);	
}

void erase(SinglyLinkedList* list, int pos) {

	if(pos >= list->size) {
		pop_back(list);
		return;
	}
	if(pos <= 0) {
		pop_front(list);
		return;
	}

	Node* curr_node = list->head;
	Node* prev = list->head;
	int i = 0;
	while(curr_node != NULL) {
		if(pos == i) {
			prev->next = curr_node->next;
			free(curr_node);
			list->size = list->size - 1;
			break;	
		}
		++i;
		prev = curr_node;
		curr_node = curr_node->next;
	}

	if(list->size == 0) {
		list->end = list->head = NULL;
	}	
}

void remove_if(SinglyLinkedList* list, bool (*cmp)(const void* data)) {

	Node* curr_node = list->head;
	Node* prev = list->head;
	while(curr_node != NULL) {
		if(cmp(curr_node->data)) {
			prev->next = curr_node->next;
			free(curr_node);
			curr_node = prev->next;
			list->size = list->size - 1;
			continue;
		}
		prev = curr_node;
		curr_node = curr_node->next;
	}

	if(list->size == 0) {
		list->end = list->head = NULL;
	}	
}

void reverse(SinglyLinkedList* list) {
	
	if(list->size <= 1) return;

	Node* prev_node = list->head;
	Node* curr_node = prev_node->next;
	Node* future_node = curr_node->next;
	while(future_node != NULL) {
		curr_node->next = prev_node;
		prev_node = curr_node;
		curr_node = future_node;
		future_node = future_node->next;
	}
	curr_node->next = prev_node;
	list->end = list->head;
	list->end->next = NULL;
	list->head = curr_node;
}

void erase_duplicates(SinglyLinkedList* list, bool (*cmp)(const void* data)) {
	Node* iCurr = list->head;
	Node* prev;
	int count = 0;
	while(iCurr != NULL) {
		if(cmp(iCurr->data)) {
			if(count == 0) count += 1;
		  	else {
				prev->next = iCurr->next;
				free(iCurr);
				iCurr = prev->next;
				list->size = list->size - 1;
		 	}
		}
		prev = iCurr;
		iCurr = iCurr->next;
	}
}

bool contains(SinglyLinkedList* list, bool (*cmp)(const void* data)) {
	Node* curr_node = list->head;
	while(curr_node != NULL) {
		if(cmp(curr_node->data)) return true;
		curr_node = curr_node->next;
	}
	return false;
}

int size(SinglyLinkedList* list) {
	return list->size;
}

bool is_empty(SinglyLinkedList* list) {
	return list->size == 0;
}

void clear(SinglyLinkedList* list) {
	Node* curr_node = list->head;
	while(curr_node != NULL) {
		Node* temp = curr_node;
		curr_node = curr_node->next;
		free(temp);
	}
	list->head = list->end = NULL;
	list->size = 0;
}

void swap(SinglyLinkedList* left, SinglyLinkedList* right) {
	Node* temp = left->head;
	left->head = right->head;
	right->head = temp;

	temp = left->end;
	left->end = right->end;
	right->end = temp;

	int size = left->size;
	left->size = right->size;
	right->size = size;
}


Node* at(SinglyLinkedList* list, int pos) {
	if(pos >= list->size) return list->end;
	if(pos <= 0) return list->head;

	Node* curr_node = list->head;
	int i = 0;
	while(i != pos && curr_node != NULL) {
		curr_node = curr_node->next;
		++i;
	}
	return curr_node;
}

void sort(SinglyLinkedList* list, bool (*cmp)(const void* left, const void* right)) {
	Node* iCurr = list->head;
	while(iCurr != NULL) {
		Node* smallest_node = iCurr;
		Node* jCurr = iCurr->next;
		while(jCurr != NULL) {
			if(cmp(jCurr->data, smallest_node->data)) {smallest_node = jCurr;}
			jCurr = jCurr->next;
		}
		void* temp = iCurr->data;
		iCurr->data = smallest_node->data;
		smallest_node->data = temp;
		iCurr = iCurr->next;
	}
}

SinglyLinkedList* new_list() {

	SinglyLinkedList *list;
	list = (SinglyLinkedList*) malloc(sizeof(SinglyLinkedList));

	if(list == NULL) return NULL;

	list->head = NULL;
	list->end  = NULL;
	list->size = 0;
	return list;
}

