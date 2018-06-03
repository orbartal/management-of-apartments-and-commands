#include "list.h"

void list_init_empty(struct LinkedList* p_list) {
	p_list->head = NULL;
	p_list->tail = NULL;
}
void list_free(struct LinkedList* p_list) {
	//TODO
}

void list_insert_node_to_list_end(struct ListNode* p_node, struct LinkedList* p_list){
	void* v = p_node->data;
	if (p_list->tail == NULL) {
		p_list->tail = p_node;
		p_list->head = p_node;
	}
	else if (p_list->tail == p_list->head) {
		p_list->tail = p_node;
		p_list->head->next = p_node;
		p_node->prev = p_list->head;
	}
	else {
		p_node->prev = p_list->tail;
		p_list->tail->next = p_node;
		p_list->tail = p_node;
	}
}

void list_for_each(struct LinkedList* p_list, void(*action)(struct ListNode*)) {
	ListNode* p_node = p_list->head;
	while (p_node!=NULL) {
		action(p_node);
		p_node = p_node->next;
	}
}