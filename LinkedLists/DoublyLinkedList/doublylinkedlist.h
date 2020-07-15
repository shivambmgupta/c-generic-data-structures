#ifndef DOUBLY_LINKED__H
#define DOUBLY_LINKED__H

#include <stdio.h>

#define bool int
#define TRUE 1
#define true 1
#define True 1
#define FALSE 0
#define False 0
#define false 0
#define OUT_OF_MEM "Out of memory!\n"

typedef struct __$$__dl_node {
	void* data;
	struct __$$__dl_node* next;
	struct __$$__dl_node* prev;
} DLNode;

typedef struct Doublylinkedlist {
	DLNode* head;
	DLNode* end;
	int   size;
} DoublyLinkedList;

DoublyLinkedList*  new_dl_list();
DLNode*   	   new_dl_node(void* data);
DLNode*   	   dl_push_back(DoublyLinkedList *list, void *data);
DLNode*   	   dl_push_front(DoublyLinkedList *list, void *data);
DLNode*   	   dl_insert(DoublyLinkedList *list, void *data, int pos);
void      	   dl_pop_back(DoublyLinkedList *list);
void      	   dl_pop_front(DoublyLinkedList *list);
DLNode*   	   dl_at(DoublyLinkedList *list, int pos);
void      	   dl_erase(DoublyLinkedList *list, int pos);
void 		   dl_erase_node(DoublyLinkedList *list, DLNode* node);
void      	   dl_erase_duplicates(DoublyLinkedList *list, bool (*cmp)(const void* data));
void      	   dl_reverse(DoublyLinkedList *list);
void      	   dl_sort(DoublyLinkedList *list, bool (*cmp)(const void* left, const void* right));
void      	   dl_clear(DoublyLinkedList *list);
bool      	   dl_is_empty(DoublyLinkedList *list);
int       	   dl_size(DoublyLinkedList *list);
bool      	   dl_contains(DoublyLinkedList *list, bool (*cmp)(const void* data));
void      	   dl_swap(DoublyLinkedList *left, DoublyLinkedList *right);

#endif
