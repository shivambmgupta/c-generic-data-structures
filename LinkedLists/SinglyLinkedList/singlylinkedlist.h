#include <stdio.h>

#define bool int
#define TRUE 1
#define true 1
#define True 1
#define FALSE 0
#define False 0
#define false 0

typedef struct node {
	void* data;
	struct node* next;
} Node;

typedef struct singlylinkedlist {
	Node* head;
	Node* end;
	int   size;
} SinglyLinkedList;

Node* push_back(SinglyLinkedList *list, void *data);
Node* push_front(SinglyLinkedList *list, void *data);
Node* insert(SinglyLinkedList *list, void *data, int pos);
void  pop_back(SinglyLinkedList *list);
void  pop_front(SinglyLinkedList *list);
Node* at(SinglyLinkedList *list, int pos);
void  erase(SinglyLinkedList *list, int pos);
void  erase_duplicates(SinglyLinkedList *list, bool (*cmp)(const void* data));
void  reverse(SinglyLinkedList *list);
void  sort(SinglyLinkedList *list, bool (*cmp)(const void* left, const void* right));
void  clear(SinglyLinkedList *list);
bool  is_empty(SinglyLinkedList *list);
int   size(SinglyLinkedList *list);
bool  contains(SinglyLinkedList *list, bool (*cmp)(const void* data));
void  swap(SinglyLinkedList *left, SinglyLinkedList *right);