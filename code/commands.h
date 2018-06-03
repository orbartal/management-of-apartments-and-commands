#ifndef COMMAND_H_
#define COMMAND_H_

#include <stdio.h>
#include <stdlib.h>
#include "app_data.h"
#include "apartments.h"
#include "errors.h"

enum CommandType {
	CommandTypeAddApartment
};

typedef struct Command
{
	enum CommandType type;
	void* arguments;
}Command;

typedef struct AddApartmentCommand
{
	size_t address_size;
	char* address;
	int price;
	int number_of_rooms;
	short int day;
	short int month;
	short int year;
}AddApartmentCommand;

int command_free(struct Command* input);
void command_print(struct Command* input);
int command_execute(struct AppDATA* appData, struct Command* command);

#endif
