#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"



typedef struct ListNode
{
	void* data;
	struct ListNode* next;
	struct ListNode* prev;
}ListNode;

typedef struct LinkedList
{
	ListNode* head;
	ListNode* tail;
}LinkedList;

void list_init_empty(struct LinkedList* p_list);
void list_free(struct LinkedList* p_list);
void list_insert_node_to_list_end(struct ListNode* p_node, struct LinkedList* p_list);
void list_for_each (struct LinkedList* p_list, void(*action)(struct ListNode*));

#endif