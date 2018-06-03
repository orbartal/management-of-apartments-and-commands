#ifndef APARTMENT_H_
#define APARTMENT_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "errors.h"

typedef struct enteranceDate
{
	short int day;
	short int month;
	short int year;
} EnteranceDate;

typedef struct apt
{
	int code;
	char *adress;
	int price;
	short int roomNum;
	short int day;
	short int month;
	short int year;
	EnteranceDate enterDate;
}Apt;

typedef struct aptListNode
{
	Apt* data;
	struct AptlistNode* next;
	struct AptlistNode* prev;
}AptListNode;

typedef struct aptList
{
	AptListNode* head;
	AptListNode* tail;
}AptList;

void apartments_list_init(struct aptList* apartments);
void apartments_list_free(struct aptList* apartments);

#endif