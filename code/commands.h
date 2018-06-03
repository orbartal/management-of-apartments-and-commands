#ifndef COMMAND_H_
#define COMMAND_H_

#include <stdio.h>
#include <stdlib.h>
#include "app_data.h"
#include "apartments.h"
#include "errors.h"

#define ADD_APT_COMMAND_TYPE 1

typedef struct command
{
	int type;
	void* arguments;
}command;

typedef struct addApartmentCommand
{
	size_t address_size;
	char* address;
	int price;
	int numberOfRooms;
	short int day;
	short int month;
	short int year;
}addApartmentCommand;

int command_free(struct command* input);
void command_print(struct command* input);
int command_execute(struct AppDATA* appData, struct command* command);

#endif
