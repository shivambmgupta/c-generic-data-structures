#ifndef SINGLY_LINKED_LIST__H
#define SINGLY_LINKED_LIST__H

#include <stdio.h>

#define bool int
#define TRUE 1
#define true 1
#define True 1
#define FALSE 0
#define False 0
#define false 0

typedef struct __$$__sl_node {
	void* data;
	struct __$$__sl_node* next;
} SLNode;

typedef struct singlylinkedlist {
	SLNode* head;
	SLNode* end;
	int   size;
} SinglyLinkedList;

SinglyLinkedList* new_sl_list();
SLNode* 	  sl_push_back(SinglyLinkedList *list, void *data);
SLNode* 	  sl_push_front(SinglyLinkedList *list, void *data);
SLNode* 	  sl_insert(SinglyLinkedList *list, void *data, int pos);
void  		  sl_pop_back(SinglyLinkedList *list);
void  		  sl_pop_front(SinglyLinkedList *list);
SLNode* 	  sl_at(SinglyLinkedList *list, int pos);
void  		  sl_erase(SinglyLinkedList *list, int pos);
void  		  sl_erase_duplicates(SinglyLinkedList *list, bool (*cmp)(const void* data));
void  	   	  sl_reverse(SinglyLinkedList *list);
void  		  sl_sort(SinglyLinkedList *list, bool (*cmp)(const void* left, const void* right));
void  		  sl_clear(SinglyLinkedList *list);
bool  		  sl_is_empty(SinglyLinkedList *list);
int   		  sl_size(SinglyLinkedList *list);
bool  		  sl_contains(SinglyLinkedList *list, bool (*cmp)(const void* data));
void  		  sl_swap(SinglyLinkedList *left, SinglyLinkedList *right);

#endif
