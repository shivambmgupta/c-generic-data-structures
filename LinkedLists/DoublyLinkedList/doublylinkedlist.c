#include <stdio.h>
#include <malloc.h>
#include "doublylinkedlist.h"

DoublyLinkedList*  new_dl_list() {
	DoublyLinkedList *list = (DoublyLinkedList*) malloc(sizeof(DoublyLinkedList));
	if(!list) {
		return NULL;
	}
	list->head = NULL;
	list->end  = NULL;
	list->size = 0;
	return list;
}

DLNode* new_dl_node(void* data) {

	DLNode *node = (DLNode*) malloc(sizeof(DLNode));
	if (!node) return NULL;

	node->data = data;
	node->next = NULL;
	node->prev = NULL;
}

DLNode* dl_push_back(DoublyLinkedList *list, void *data) {

	if(!list) return NULL;

	DLNode* node = new_dl_node(data);
	if(!node) {
		fputs(OUT_OF_MEM, stderr);
		return NULL;
	}
	
	if(list->end == NULL) {
		list->end = node;
		list->head = node;
		list->size = list->size + 1;
		return node;
	}

	node->prev = list->end;
	list->end->next = node;
	list->end = node;
	list->size = list->size + 1;
	return node;
}

DLNode* dl_push_front(DoublyLinkedList *list, void *data) {

	if(!list) return NULL;

	DLNode* node = new_dl_node(data);
	if(!node) {
		fputs(OUT_OF_MEM, stderr);
		return NULL;
	}
	
	if(!list->head) {
		list->head = node;
		list->end = node;
		list->size = list->size + 1;
		return node;
	}
	
	list->head->prev = node;
	node->next = list->head;
	list->head = node;
	list->size = list->size + 1;
	return node;
}

DLNode* dl_insert(DoublyLinkedList *list, void *data, int pos) {

	if(!list) return NULL;

	if(pos >= list->size) return dl_push_back(list, data);
	if(pos <= 0)	      return dl_push_front(list, data);

	DLNode* node = new_dl_node(data);
	if(!node) {
		fputs(OUT_OF_MEM, stderr);
		return NULL;
	}
	
	int i = 1;
	DLNode* curr_node = list->head;
	while(i < pos) {
		curr_node = curr_node->next;
		++i;
	}
	node->prev = curr_node;
	node->next = curr_node->next;

	if(curr_node->next) (curr_node->next)->prev = node;
	curr_node->next = node;

	list->size = list->size + 1;
	return node;
}

void  dl_pop_back(DoublyLinkedList *list) {
	if(list == NULL || list->size == 0) return;

	if(list->size == 1) {
		free(list->head);
		list->head = NULL;
		list->end = NULL;
		list->size = 0;
		return;
	}

	DLNode* temp = list->end;
	list->end = list->end->prev;
	list->end->next = NULL;
	list->size = list->size - 1;
	free(temp);
}

void  dl_pop_front(DoublyLinkedList *list) {
	if(list == NULL || list->size == 0) return;

	if(list->size == 1) {
		free(list->head);
		list->head = NULL;
		list->end = NULL;
		list->size = 0;
		return;
	}

	DLNode* temp = list->head;
	list->head = list->head->next; //Since size > 1, it is guranteed that list->head->next exists.
	list->head->prev = NULL;
	list->size = list->size - 1;
	free(temp);
}

DLNode* dl_at(DoublyLinkedList *list, int pos) {
	if(!(list && list->size)) return NULL;
	if(pos >= list->size - 1) return list->end;
	if(pos <= 0)		  return list->head;

	int i = 0;
	DLNode* curr_node = list->head;
	while(i != pos && curr_node != NULL) {
		curr_node = curr_node->next;
		++i;
	}
	return curr_node;
}

void  dl_erase(DoublyLinkedList *list, int pos) {

	if(!(list && list->size)) return NULL;
	
	if(pos >= list->size - 1) {
		dl_pop_back(list);
		return;
	}
	if(pos <= 0) {
		dl_pop_front(list);
		return;
	}

	DLNode* node = dl_at(list, pos);
	if(!node) return;

	DLNode* prev_node = node->prev;
	DLNode* next_node = node->next;

	prev_node->next = next_node;
	next_node->prev = prev_node;
	list->size = list->size - 1;
	free(node);
}

void dl_erase_node(DoublyLinkedList *list, DLNode* node) {

	if(list == NULL || list->size == 0) return;
	if(!node) return;

	//If node is head node
	if(node == list->head) {
		dl_pop_front(list);
		return;
	}

	//If node is end node
	if(node == list->end) {
		dl_pop_back(list);
		return;
	}

	DLNode* curr_node = list->head;
	while(curr_node != NULL) {
		if(curr_node == node) {
			DLNode* prev = node->prev;
			DLNode* next = node->next;
			if(prev && next) {
				prev->next = next;
				next->prev = prev;
			}
			else if(prev) prev->next = NULL;
			else next->prev = NULL;
			list->size = list->size - 1;
			free(curr_node);
			break;
		}
		curr_node = curr_node->next;
	}	
}


void  dl_erase_duplicates(DoublyLinkedList *list, bool (*cmp)(const void* data)) {
	if(!(list && list->size)) return;
	int occurences = 0;
	DLNode* curr_node = list->head; 
	while(curr_node != NULL) { 
		if(cmp(curr_node->data)) {
			if(occurences == 0) occurences += 1;
			else {
				DLNode* temp = curr_node;
				curr_node = curr_node->next;
				dl_erase_node(list, temp);
				continue;
			}
		}
		curr_node = curr_node->next;
	}	
}

void  dl_reverse(DoublyLinkedList *list) {
	if(!(list && list->size)) return;	
	DLNode* curr_node = list->head;
	DLNode* temp;
	while(curr_node != NULL) {
		DLNode* curr = curr_node;
		curr_node = curr_node->next;
		temp = curr->prev;
		curr->prev = curr->next;
		curr->next = temp;	
	}
	temp = list->head;
	list->head = list->end;
	list->end = temp;
}

void  dl_sort(DoublyLinkedList *list, bool (*cmp)(const void* left, const void* right)) {
	if(!(list && list->size)) return;
	DLNode* iCurr = list->head;
	while(iCurr != NULL) {
		DLNode* smallest = iCurr;
		DLNode* jCurr = iCurr->next;
		while(jCurr != NULL) {
			if(cmp(jCurr->data, smallest->data)) smallest = jCurr;
			jCurr = jCurr->next;
		}
		void* temp = smallest->data;
		smallest->data = iCurr->data;
		iCurr->data = temp;
		iCurr = iCurr->next;
	}
}

void  dl_clear(DoublyLinkedList *list) {
	if(!(list && list->size)) return;
	while(list->size != 0) dl_pop_back(list);
}

bool  dl_is_empty(DoublyLinkedList *list) {
	if(!(list && list->size)) true;
	return list->size == 0;
}

int   dl_size(DoublyLinkedList *list) {
	if(!(list && list->size)) return 0;
	return list->size;
}

bool  dl_contains(DoublyLinkedList *list, bool (*cmp)(const void* data)) {
	if(!(list && list->size)) return false;
	for(DLNode* curr_node = list->head; curr_node != NULL; curr_node = curr_node->next)
		if(cmp(curr_node->data))
			return true;
	return false;
}

void  dl_swap(DoublyLinkedList *left, DoublyLinkedList *right) {
	if(!(left && right)) return;
	
	DLNode* temp = left->head;
	left->head = right->head;
	right->head = temp;

	temp = left->end;
	left->end = right->end;
	right->end = temp;

	int size = left->size;
	left->size = right->size;
	right->size = size;
}
