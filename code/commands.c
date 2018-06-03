#include "commands.h"

void command_print_add_apartment_command(struct addApartmentCommand* input);
int command_add_apartment_execute(struct appDATA* p_app_data, struct addApartmentCommand* p_command);

int command_free(struct command* input) {
	if (input->type == ADD_APT_COMMAND_TYPE) {
		//printf("\ncommand_free addApartmentCommand\n");
		struct addApartmentCommand* arguments = input->arguments;
		free(arguments->address);
	}
	free(input);
	return METHOD_SUCCESS;
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

int command_execute(struct appDATA* p_app_data, struct command* command) {
	if (command->type == ADD_APT_COMMAND_TYPE) {
		command_add_apartment_execute(p_app_data, command->arguments);
		return METHOD_SUCCESS;
	}
	return METHOD_FAILURE;
}

int command_add_apartment_execute(struct appDATA* p_app_data, struct addApartmentCommand* p_command) {
	struct apt* p_new_apt = malloc(sizeof(struct apt));
	error_if_condition_true_print_and_exit((p_new_apt == NULL), "malloc return NULL on 'p_new_apt' in 'commands.c'");
	p_new_apt->address = malloc(sizeof(char)*p_command->address_size);
	error_if_condition_true_print_and_exit((p_new_apt->address == NULL), "malloc return NULL on 'p_new_apt->address' in 'commands.c'");
	p_new_apt->address_size = p_command->address_size;
	int result = strncpy_s(p_new_apt->address, p_new_apt->address_size, p_command->address, p_command->address_size - 1);
	if (result != 0) {
		free(p_new_apt->address);
		free(p_new_apt);
		return METHOD_FAILURE;
	}
	p_new_apt->code = p_app_data->last_apartment_code++;
	p_new_apt->price = p_command->price;
	p_new_apt->number_Of_rooms = p_command->numberOfRooms;
	p_new_apt->day = p_command->day;
	p_new_apt->month = p_command->month;
	p_new_apt->year = p_command->year;
	p_app_data->apt_temp = p_new_apt; //TODO: remove
	apartments_add_new_apartment(p_new_apt, p_app_data->apartments);
	return METHOD_SUCCESS;
}