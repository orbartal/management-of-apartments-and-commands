#include "list.h"

//Define private methods. Will be used only by methods in this c file. Unknown outside of it.
void list_insert_node_to_a_sorted_list(struct LinkedList* p_list, struct ListNode* p_node, bool(*comparable)(struct ListNode*, struct ListNode*));
void list_insert_node_data_to_a_sorted_list(struct LinkedList* p_list, void* p_data, bool(*comparable)(struct ListNode*, struct ListNode*));

//Basic node actions
void list_init_node(struct ListNode* p_node, struct ListNode* p_node_prev, void* data, struct ListNode* p_node_next) {
	p_node->prev = p_node_prev;
	p_node->data = data;
	p_node->next = p_node_next;
}

//Basic list actions o(1)
void list_init_empty(struct LinkedList* p_list) {
	p_list->size = 0; 
	p_list->head = NULL;
	p_list->tail = NULL;
}

void list_insert_node_to_list_end(struct LinkedList* p_list, struct ListNode* p_node) {
	//Node 'p_node' will become the new tail node in list 'p_list'.
	//case 1: The list is empty. Node p_node will become both its head, tail and its single node.
	if (p_list->tail == NULL) {
		p_list->tail = p_node;
		p_list->head = p_node;
	}
	//case 2: The list has a single node. 
	else if (p_list->tail == p_list->head) {
		p_list->tail = p_node;
		p_list->head->next = p_node;
		p_node->prev = p_list->head;
	}
	//case 3: The list has a more than one node.
	else {
		p_node->prev = p_list->tail;
		p_list->tail->next = p_node;
		p_list->tail = p_node;
	}
	p_list->size++;
}

void list_remove_node_from_list(struct LinkedList* p_list_input, ListNode* p_node) {
	//We assume the list and the node are not null and that the list contain the node.
	ListNode* p_prev = p_node->prev;
	ListNode* p_next = p_node->next;
	if ((p_prev != NULL) && (p_next != NULL)) { //Not tail and not head but a normal node in the list
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
	p_list_input->size--;
}

//Genric methods o(n)
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

void list_filter_by_predict(struct LinkedList* p_list_input, struct LinkedList* p_list_output, void* predict_data, bool(*predict)(struct ListNode*, void*)) {
	ListNode* p_node = p_list_input->head;
	while (p_node != NULL) {
		if (predict(p_node, predict_data) == true) {
			struct ListNode* p_new_node = malloc(sizeof(struct ListNode));
			error_if_condition_true_print_and_exit((p_new_node == NULL), "malloc return NULL on 'p_new_node' in 'list.c'");
			list_init_node(p_new_node, NULL, p_node->data, NULL);
			list_insert_node_to_list_end(p_list_output, p_new_node);
		}
		p_node = p_node->next;
	}
}

void list_for_each(struct LinkedList* p_list, void(*action)(struct ListNode*)) {
	ListNode* p_node = p_list->head, *p_node_next = NULL;
	while (p_node != NULL) {
		p_node_next = p_node->next;
		action(p_node);
		p_node = p_node_next;
	}
}

//Complicate methods that use the genric methods o(n)
void list_free_list_and_all_nodes_but_not_data(struct LinkedList* p_list) {
	list_for_each(p_list, free);
	free(p_list);
}

void list_sort_by_comparable(struct LinkedList* p_list_input, struct LinkedList* p_list_output, bool(*comparable)(struct ListNode*, struct ListNode*)) {
	ListNode* p_node = p_list_input->head;
	while (p_node != NULL) {
		list_insert_node_data_to_a_sorted_list(p_list_output, p_node->data, comparable);
		p_node = p_node->next;
	}
}

void list_insert_node_data_to_a_sorted_list(struct LinkedList* p_list, void* p_data, bool(*comparable)(struct ListNode*, struct ListNode*)){
	struct ListNode* p_node = malloc(sizeof(struct ListNode));
	error_if_condition_true_print_and_exit((p_node == NULL), "malloc return NULL on 'p_node' in 'list.c'");
	p_node->next = NULL;
	p_node->prev = NULL;
	p_node->data = p_data;
	list_insert_node_to_a_sorted_list(p_list, p_node, comparable);
}

void list_insert_node_to_a_sorted_list(struct LinkedList* p_list, struct ListNode* p_new_node, bool(*comparable)(struct ListNode*, struct ListNode*)) {
	//We assume 'p_list' is a sorted list by 'comparable'. The 'p_new_node' will be inserted to 'p_list' that it remain sorted.
	//For simplicity and clarity of speech we shell assume the list is sorted from largest, head, to smallest, tail. 
	struct ListNode* p_node_old = NULL; //'p_node_old' is the largest node in 'p_list' that is smaller than 'p_new_node'
	p_node_old = list_find_node_by_predict(p_list, p_new_node, comparable); // bool(*comparable)(struct ListNode*, p_new_node)
	//case 1: 'p_new_node' is smaller than any element in the list 'p_list'. Thus 'p_new_node' is the new tail. 
	if (p_node_old == NULL) {
		list_insert_node_to_list_end(p_list, p_new_node);
	}
	//case 2: 'p_new_node' is larger than 'p_node_old' but smaller than all the elements befor it
	else {
		//case 2.1: 'p_new_node' is larger than any element in the list 'p_list'. Thus 'p_new_node' is the new header. 
		if (p_list->head == p_node_old) {
			p_new_node->next = p_node_old;
			p_node_old->prev = p_new_node;
			p_list->head = p_new_node;
		}
		//case 2.2: At least one node is larger and at least one node is smaller than 'p_new_node'. Thus 'p_new_node' is not header or tail.
		else {
			struct ListNode* prev = p_node_old->prev;
			p_new_node->prev = prev;
			p_new_node->next = p_node_old;
			p_node_old->prev = p_new_node;
			prev->next = p_new_node;
		}
	}
}
