#ifndef APARTMENT_H_
#define APARTMENT_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "errors.h"
#include "list.h"

typedef struct enteranceDate
{
	short int day;
	short int month;
	short int year;
} EnteranceDate;

typedef struct apt
{
	int code;
	size_t address_size;
	char *address;
	int price;
	short int number_Of_rooms;
	short int day;
	short int month;
	short int year;
	//EnteranceDate enterDate;
}Apt;

void apartments_print_one_node(struct ListNode* apartment);
void apartments_print_one_apartment(struct apt* apartment);
void apartments_print_entire_list(struct LinkedList* p_apartments_list);
void apartments_add_new_apartment(struct apt* p_new_apartment, struct LinkedList* p_apartments_list);

#endif