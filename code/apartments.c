#include "apartments.h"

//Define private methods. Will be used only by methods in this c file. Unknown outside of it.
bool apartments_predict_with_code(struct ListNode* p_node, int* p_code);
bool apartments_predict_is_seconde_price_higher(struct Apartment* p_apartment_1, struct Apartment* p_apartment_2);


//Print to console
void apartments_print_one_apartment(struct Apartment* input) {
	printf("Apt details:\n");
	printf("Code: %d\n", input->code);
	printf("Address: %s\n", input->address);
	printf("Number of rooms: %d\n", input->number_Of_rooms);
	printf("Price: %d\n", input->price);
	printf("Entry date: %d.%d.%d\n", input->day, input->month, input->year);
	printf("Database entry date: %d.%d.%d\n", input->day, input->month, input->year);//TODO
}

void apartments_print_one_node(struct ListNode* input) {
	struct Apartment* apartment = (struct Apartment*)input->data;
	apartments_print_one_apartment(apartment);
}

void apartments_print_entire_list(struct LinkedList* p_apartments_list) {
	list_for_each(p_apartments_list, apartments_print_one_node);
}

//Free memory
void apartments_free_one_apartment(struct Apartment* apartment) {
	free(apartment->address);
	free(apartment);
}

void apartments_free_one_apartment_in_node(struct ListNode* node) {
	apartments_free_one_apartment(node->data);
}

//Change list: add or remove Apartment from list
void apartments_add_new_apartment(struct Apartment* p_new_apartment, struct LinkedList* p_apartments_list) {
	struct ListNode* p_node = NULL;
	p_node = malloc(sizeof(struct ListNode));
	error_if_condition_true_print_and_exit((p_node == NULL), "malloc return NULL on 'p_node' in 'apartments.c'");
	p_node->next = NULL;
	p_node->prev = NULL;
	p_node->data = p_new_apartment;
	list_insert_node_to_list_end(p_apartments_list, p_node);
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

bool apartments_comparable_by_price_low_to_high(struct ListNode* p_node_1, struct ListNode* p_node_2) {
	return apartments_predict_is_seconde_price_higher(p_node_2->data, p_node_1->data);
}

//we shell assume the list is sorted from largest, head, to smallest, tail.
//(struct ListNode*, p_new_node)

bool apartments_comparable_by_price_high_to_low(struct ListNode* p_node_1, struct ListNode* p_node_2) {
	return apartments_predict_is_seconde_price_higher(p_node_1->data, p_node_2->data);
}

bool apartments_predict_is_seconde_price_higher(struct Apartment* p_apartment_1, struct Apartment* p_apartment_2) {
	return (p_apartment_1->price < p_apartment_2->price);
}