#ifndef COMMAND_H_
#define COMMAND_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "app_data.h"
#include "apartments.h"
#include "errors.h"

enum CommandType {
	CommandTypeAddApartment,
	CommandTypeBuyApartment,
	CommandTypeDeleteApartment,
	CommandTypeGetApartments,
	CommandTypeAddExit,
	CommandTypeUnknown
};

enum SortType {
	SortTypeByPriceLowToHigh,
	SortTypeByPriceHighToLow,
	SortTypeNoSort
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

typedef struct BuyApartmentCommand
{
	int code;
}BuyApartmentCommand;

typedef struct GetApartmentsCommand
{
	int number_of_parameters;
	char** parameters;
	int min_rooms;
	int max_rooms;
	int min_price;
	int max_price;
	//time_t min_date;
	//time_t max_date;
	enum SortType sort_type;
}GetApartmentsCommand;

int command_free(struct Command* input);
void command_print(struct Command* input);
int command_execute(struct AppDATA* appData, struct Command* command);
void command_init_get_apartments_command(struct GetApartmentsCommand* command);


#endif
