#include "apartments.h"

bool apartments_predict_with_code(struct ListNode* p_node, int* p_code);


void apartments_print_entire_list(struct LinkedList* p_apartments_list) {
	list_for_each(p_apartments_list, apartments_print_one_node);
}

void apartments_print_one_node(struct ListNode* input) {
	struct Apartment* apartment = (struct Apartment*)input->data;
	apartments_print_one_apartment(apartment);
}
void apartments_print_one_apartment(struct Apartment* input) {
	printf("Apt details:\n");
	printf("Code: %d\n", input->code);
	printf("Address: %s\n", input->address);
	printf("Number of rooms: %d\n", input->number_Of_rooms);
	printf("Price: %d\n", input->price);
	printf("Entry date: %d.%d.%d\n", input->day, input->month, input->year);
	printf("Database entry date: %d.%d.%d\n", input->day, input->month, input->year);//TODO
}

void apartments_add_new_apartment(struct Apartment* p_new_apartment, struct LinkedList* p_apartments_list) {
	struct ListNode* p_node = NULL;
	p_node = malloc(sizeof(struct ListNode));
	error_if_condition_true_print_and_exit((p_node == NULL), "malloc return NULL on 'p_node' in 'apartments.c'");
	p_node->next = NULL;
	p_node->prev = NULL;
	p_node->data = p_new_apartment;
	list_insert_node_to_list_end(p_node, p_apartments_list);
}

void apartments_buy_apartment_with_code(struct LinkedList* p_apartments_list, int code) {
	struct ListNode* p_node = list_find_node_by_predict(p_apartments_list, &code, apartments_predict_with_code);
	list_remove_node_from_list(p_apartments_list, p_node);
}

bool apartments_predict_with_code(struct ListNode* p_node, int* p_code) {
	struct Apartment* apartment = (struct Apartment*) p_node->data;
	int code1 = apartment->code;
	int code2 = *p_code;
	return code1 == code2;
}

void apartments_free_one_apartment(struct Apartment* apartment) {
	//TODO
}

void apartments_free_one_apartment_in_node(struct ListNode* node) {
	apartments_free_one_apartment(node->data);
}