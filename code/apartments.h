#ifndef APARTMENT_H_
#define APARTMENT_H_

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "list.h"

//struct: Apartment
typedef struct Apartment
{
	int code;
	size_t address_size;
	char *address;
	int price;
	short int number_Of_rooms;
	short int day;
	short int month;
	short int year;
}Apartment;

//print
void apartments_print_one_node(struct ListNode* node);
void apartments_print_one_apartment(struct Apartment* apartment);
void apartments_print_entire_list(struct LinkedList* p_apartments_list);

//Free memory
void apartments_free_one_apartment(struct Apartment* apartment);
void apartments_free_one_apartment_in_node(struct ListNode* node);

//Change list: add or remove Apartment from list
void apartments_add_new_apartment(struct Apartment* p_new_apartment, struct LinkedList* p_apartments_list);
void apartments_buy_apartment_with_code(struct LinkedList* p_apartments_list, int code);

#endif