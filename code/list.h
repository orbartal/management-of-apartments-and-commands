#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"



typedef struct ListNode
{
	void* data;
	struct ListNode* next;
	struct ListNode* prev;
}ListNode;

typedef struct LinkedList
{
	int size; //Used only for debug.
	ListNode* head;
	ListNode* tail;
}LinkedList;

//TODO return int and check for errors?
void list_init_empty(struct LinkedList* p_list);
void list_free(struct LinkedList* p_list);
void list_free_list_and_all_nodes_but_not_data(struct LinkedList* p_list);
void list_free_list_and_all_nodes_and_data(struct LinkedList* p_list);
void list_insert_node_to_list_end(struct ListNode* p_node, struct LinkedList* p_list);
void list_for_each (struct LinkedList* p_list, void(*action)(struct ListNode*));
void list_filter_by_predict(struct LinkedList* p_list_input, struct LinkedList* p_list_output, void* predict_data, bool(*predict)(struct ListNode*, void*));
struct ListNode* list_find_node_by_predict(struct LinkedList* p_list_input, void* predict_data, bool(*predict)(struct ListNode*, void*));
void list_remove_node_from_list(struct LinkedList* p_list_input, ListNode* p_node);
void list_init_node(struct ListNode* p_node, struct ListNode* p_node_prev, void* data, struct ListNode* p_node_next);

#endif