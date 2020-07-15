#ifndef SINGLY_LINKED_LIST__C
#define SINGLY_LINKED_LIST__C

#include <stdio.h>
#include <malloc.h>
#include "singlylinkedlist.h"

SinglyLinkedList* this;

SLNode* sl_push_back(SinglyLinkedList* list, void *data) {

	if(!list) return NULL;

	SLNode* node = (SLNode*) malloc(sizeof(SLNode));
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

SLNode* sl_push_front(SinglyLinkedList* list, void *data) {

	if(!list) return NULL;

	SLNode *node = (SLNode*) malloc(sizeof(SLNode));
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

SLNode* sl_insert(SinglyLinkedList* list, void *data, int pos) {

	if(!list) return NULL;

	if(pos >= list->size) return sl_push_back(list, data);
	if(pos <= 0) 	      return sl_push_front(list, data);

	SLNode *node = (SLNode*) malloc(sizeof(SLNode));
	if(node == NULL)  return NULL; //Out of Memory

	node->data = data;

	int i = 1;
	SLNode* curr_node = list->head;
	while( i < pos ) {
		curr_node = curr_node->next;
		++i;
	}
	node->next = curr_node->next;
	curr_node->next = node;
	list->size = list->size + 1;
	return node;

}

void sl_pop_back(SinglyLinkedList *list) {

	if(!(list && list->size)) return;

	if(list->size == 1) {
		//list->head = list->end
		free(list->end);
		list->head = NULL;
		list->end  = NULL;
		list->size = 0;
		return;
	}

	//list->head != list->end

	SLNode* curr_node = list->head;
	while(curr_node->next != list->end) curr_node = curr_node->next;
	curr_node->next = NULL;
	free(list->end);
	list->end = curr_node;
	list->size = list->size - 1;
}

void sl_pop_front(SinglyLinkedList *list) {

	if(!(list && list->size)) return;

	if(list->size == 1) {
		//list->head = list->end
		free(list->end);
		list->head = NULL;
		list->end  = NULL;
		list->size = 0;
		return;
	}

	//list->head != list->end

	SLNode* temp = list->head;
	list->head = temp->next;
	list->size = list->size - 1;
	free(temp);
}

void sl_erase(SinglyLinkedList* list, int pos) {

	if(!(list && list->size)) return;

	if(pos >= list->size) {
		sl_pop_back(list);
		return;
	}
	if(pos <= 0) {
		sl_pop_front(list);
		return;
	}

	SLNode* curr_node = list->head;
	SLNode* prev = list->head;
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

void sl_remove_if(SinglyLinkedList* list, bool (*cmp)(const void* data)) {

	if(!(list && list->size)) return;

	SLNode* curr_node = list->head;
	SLNode* prev = list->head;
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

void sl_reverse(SinglyLinkedList* list) {

	if(!(list && list->size)) return;

	SLNode* prev_node = list->head;
	SLNode* curr_node = prev_node->next;
	SLNode* future_node = curr_node->next;
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

void sl_erase_duplicates(SinglyLinkedList* list, bool (*cmp)(const void* data)) {

	if(!(list && list->size)) return;

	SLNode* iCurr = list->head;
	SLNode* prev;
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

bool sl_contains(SinglyLinkedList* list, bool (*cmp)(const void* data)) {

	if(!(list && list->size)) return false;

	SLNode* curr_node = list->head;
	while(curr_node != NULL) {
		if(cmp(curr_node->data)) return true;
		curr_node = curr_node->next;
	}
	return false;
}

int sl_size(SinglyLinkedList* list) {
	if(!(list && list->size)) return 0;
	return list->size;
}

bool sl_is_empty(SinglyLinkedList* list) {
	if(!(list && list->size)) return true;
	return list->size == 0;
}

void sl_clear(SinglyLinkedList* list) {

	if(!(list && list->size)) return;
	SLNode* curr_node = list->head;
	while(curr_node != NULL) {
		SLNode* temp = curr_node;
		curr_node = curr_node->next;
		free(temp);
	}
	list->head = list->end = NULL;
	list->size = 0;
}

void sl_swap(SinglyLinkedList* left, SinglyLinkedList* right) {

	if(!(left && right)) return;

	SLNode* temp = left->head;
	left->head = right->head;
	right->head = temp;

	temp = left->end;
	left->end = right->end;
	right->end = temp;

	int size = left->size;
	left->size = right->size;
	right->size = size;
}


SLNode* sl_at(SinglyLinkedList* list, int pos) {

	if(!(list && list->size)) return NULL;

	if(pos >= list->size) return list->end;
	if(pos <= 0) return list->head;

	SLNode* curr_node = list->head;
	int i = 0;
	while(i != pos && curr_node != NULL) {
		curr_node = curr_node->next;
		++i;
	}
	return curr_node;
}

void sl_sort(SinglyLinkedList* list, bool (*cmp)(const void* left, const void* right)) {

	if(!(list && list->size)) return;

	SLNode* iCurr = list->head;
	while(iCurr != NULL) {
		SLNode* smallest_node = iCurr;
		SLNode* jCurr = iCurr->next;
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

SinglyLinkedList* new_sl_list() {

	SinglyLinkedList *list;
	list = (SinglyLinkedList*) malloc(sizeof(SinglyLinkedList));

	if(list == NULL) return NULL;

	list->head = NULL;
	list->end  = NULL;
	list->size = 0;
	return list;
}

#endif
