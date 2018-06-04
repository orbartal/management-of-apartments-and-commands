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

void list_filter_by_predict(struct LinkedList* p_list_input, struct LinkedList* p_list_output, void* predict_data, bool(*predict)(struct ListNode*, void*)){
	ListNode* p_node = p_list_input->head;
	while (p_node != NULL) {
		if (predict(p_node, predict_data)==true) {
			list_insert_node_to_list_end(p_node, p_list_output);
		}
		p_node = p_node->next;
	}
}

struct ListNode* list_find_node_by_predict(struct LinkedList* p_list_input, void* predict_data, bool(*predict)(struct ListNode*, void*)) {
	ListNode* p_node = p_list_input->head;
	while (p_node != NULL) {
		if (predict(p_node, predict_data) == true) {
			return p_node;
		}
		p_node = p_node->next;
	}
	return NULL;
}

//We assume the list and the node are not null and that the list contain the node.
void list_remove_node_from_list(struct LinkedList* p_list_input, ListNode* p_node) {
	ListNode* p_prev = p_node->prev;
	ListNode* p_next = p_node->next;
	if ((p_prev!=NULL) && (p_next!=NULL)){ //Not tail and not head but a normal node in the list
		p_prev->next = p_next;
		p_next->prev = p_prev;
	}
	else if ((p_prev == NULL) && (p_next != NULL)) { //Tail not head
		p_list_input->head = p_next;
		p_next->prev = NULL;
	}
	else if ((p_prev != NULL) && (p_next == NULL)) { //Head not tail
		p_list_input->tail = p_prev;
		p_prev->next = NULL;
	}
	else if ((p_prev == NULL) && (p_next == NULL)) { //Tail and Head. This is the only node in the list
		p_list_input->head = NULL;
		p_list_input->tail = NULL;
	}
}