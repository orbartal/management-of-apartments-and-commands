#include "commands.h"

void command_print_add_apartment_command(struct AddApartmentCommand* input);
int command_add_apartment_execute(struct AppDATA* p_app_data, struct AddApartmentCommand* p_command);
int command_buy_apartment_execute(struct AppDATA* p_app_data, struct BuyApartmentCommand* p_command);
int command_get_apartments_execute(struct AppDATA* p_app_data, struct GetApartmentsCommand* p_command);
bool command_predict_apartment_price_and_number_of_rooms(struct ListNode* p_node, GetApartmentsCommand* command);

int command_free(struct Command* input) {
	if (input->type == CommandTypeAddApartment) {
		struct AddApartmentCommand* arguments = input->arguments;
		free(arguments->address);
	}
	free(input);
	return METHOD_SUCCESS;
}
void command_print(struct Command* input) {
	if (input->type == CommandTypeAddApartment) {
		command_print_add_apartment_command((struct AddApartmentCommand*)input->arguments);
	}
}

void command_print_add_apartment_command(struct AddApartmentCommand* input) {
	printf("\ncommand_print_add_apartment_command:\n");
	printf("\naddress_size is %d\n", input->address_size);
	printf("\naddress is %s\n", input->address);
	printf("\nprice is %d\n", input->price);
	printf("\nnumberOfRooms is %d\n", input->number_of_rooms);
	printf("\nday is %d\n", input->day);
	printf("\nmonth is %d\n", input->month);
	printf("\nyear is %d\n", input->year);
}

int command_execute(struct AppDATA* p_app_data, struct Command* command) {
	if (command->type == CommandTypeAddApartment) {
		command_add_apartment_execute(p_app_data, command->arguments);
		return METHOD_SUCCESS;
	}
	if (command->type == CommandTypeGetApartments) {
		command_get_apartments_execute(p_app_data, command->arguments);
		return METHOD_SUCCESS;
	}
	if (command->type == CommandTypeBuyApartment) {
		command_buy_apartment_execute(p_app_data, command->arguments);
		return METHOD_SUCCESS;
	}
	if (command->type == CommandTypeDeleteApartment) {
		//TODO
		return METHOD_SUCCESS;
	}
	if (command->type == CommandTypeAddExit) {
		//TODO
		return METHOD_SUCCESS;
	}
	return METHOD_FAILURE;
}

int command_add_apartment_execute(struct AppDATA* p_app_data, struct AddApartmentCommand* p_command) {
	struct Apartment* p_new_apt = malloc(sizeof(struct Apartment));
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
	p_new_apt->number_Of_rooms = p_command->number_of_rooms;
	p_new_apt->day = p_command->day;
	p_new_apt->month = p_command->month;
	p_new_apt->year = p_command->year;
	apartments_add_new_apartment(p_new_apt, p_app_data->apartments);
	return METHOD_SUCCESS;
}

int command_buy_apartment_execute(struct AppDATA* p_app_data, struct BuyApartmentCommand* p_command) {
	apartments_buy_apartment_with_code(p_app_data->apartments, p_command->code);
	return METHOD_SUCCESS;
}

void command_init_get_apartments_command(struct GetApartmentsCommand* input) {
	input->min_rooms = 0;
	input->max_rooms = INT_MAX;
	input->min_price = 0;
	input->max_price = INT_MAX;
	input->sort_type = SortTypeNoSort;
}

bool command_predict_apartment_price_and_number_of_rooms(struct ListNode* p_node, GetApartmentsCommand* command) {
	Apartment* apartment = (Apartment*) p_node->data;
	bool max_price = (command->max_price >= apartment->price);
	bool min_price = (command->min_price <= apartment->price);
	bool max_rooms = (command->max_rooms >= apartment->number_Of_rooms);
	bool min_rooms = (command->min_rooms <= apartment->number_Of_rooms);
	bool result = (max_price && min_price && max_rooms && min_rooms);
	return result;
}

int command_get_apartments_execute(struct AppDATA* p_app_data, struct GetApartmentsCommand* p_command) {
	LinkedList* original_list = p_app_data->apartments;
	LinkedList* filter_list = NULL;
	filter_list = malloc(sizeof(LinkedList));
	error_if_condition_true_print_and_exit((filter_list == NULL), "malloc return NULL on 'filter_list' in 'commands.c'");
	list_init_empty(filter_list);
	list_filter_by_predict(original_list, filter_list, p_command, command_predict_apartment_price_and_number_of_rooms);
	apartments_print_entire_list(filter_list);
	//TODO: free memory of list
	return METHOD_SUCCESS;
}