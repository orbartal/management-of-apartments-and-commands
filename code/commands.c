#include "commands.h"

int command_free(struct command* input) {
	if (input->type == ADD_APT_COMMAND_TYPE) {
		//printf("\ncommand_free addApartmentCommand\n");
		struct addApartmentCommand* arguments = input->arguments;
		free(arguments->address);
	}
	free(input);
}
void command_print(struct command* input) {
	if (input->type == ADD_APT_COMMAND_TYPE) {
		command_print_add_apartment_command((struct addApartmentCommand*)input->arguments);
	}
}

void command_print_add_apartment_command(struct addApartmentCommand* input) {
	printf("\ncommand_print_add_apartment_command:\n");
	printf("\naddress_size is %d\n", input->address_size);
	printf("\naddress is %s\n", input->address);
	printf("\nprice is %d\n", input->price);
	printf("\nnumberOfRooms is %d\n", input->numberOfRooms);
	printf("\nday is %d\n", input->day);
	printf("\nmonth is %d\n", input->month);
	printf("\nyear is %d\n", input->year);
}