#ifndef COMMAND_H_
#define COMMAND_H_

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "app_data.h"
#include "apartments.h"
#include "errors.h"

//structs: command and its data.

//What kind of command it is. 
enum CommandType {
	CommandTypeAddApartment,	//add-an-apt (insert one apartment to app_data)
	CommandTypeBuyApartment,	//buy-an-apt (remove one apartment from app_data)
	CommandTypeDeleteApartment, //delete-an-apt
	CommandTypeGetApartments,	//get-an-apt (print apartments in app_data)
	CommandTypeAddExit,			//exit (save app_data to file and exit software)
	CommandTypeUnknown			//Any thing else (will be ignored by software).
};

//Use by the get-an-apt command. If to sort apartment by price or insertion order.
enum SortType {
	SortTypeByPriceLowToHigh, //-s
	SortTypeByPriceHighToLow, //-sr
	SortTypeNoSort //
};

//Represent any type of command. However different command type use different arguments.
typedef struct Command
{
	enum CommandType type;
	void* arguments;
}Command;

//The arguments of add-an-apt command.
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

//The arguments of buy-an-apt command.
typedef struct BuyApartmentCommand
{
	int code;
}BuyApartmentCommand;

//The arguments of get-an-apt command. It has 4 predicuts and a sorting type ('-s', '-sr', '').
typedef struct GetApartmentsCommand
{
	int min_rooms;
	int max_rooms;
	int min_price;
	int max_price;
	enum SortType sort_type;
}GetApartmentsCommand;

//Methods that are common to all commands
void command_print(struct Command* input);
int command_free(struct Command* input);
int command_execute(struct AppDATA* appData, struct Command* command);

//Methods that are for only one type of command
void command_init_get_apartments_command(struct GetApartmentsCommand* command);

#endif
