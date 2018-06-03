#ifndef COMMAND_H_
#define COMMAND_H_

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

#endif
