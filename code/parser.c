#include "parser.h"

//Define private methods. Will be used only by methods in this c file. Unknown outside of it.

//Used for all command.
size_t count_arguments_in_command_line(char* input, size_t input_max_length);
int arguments_index_in_command_line(char* input, size_t input_max_length, size_t* output, size_t output_length);
int set_command_type(char* input, size_t input_max_length, size_t* index_array, struct Command* output);
enum CommandType get_command_type_by_command_name(char* command_name);
int parse_and_set_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct Command* output);

//Used only for one type of command.
int parse_and_set_add_apartment_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct Command* output);
int parse_and_set_buy_apartment_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct Command* output);
//Used only for one type of command: get-an-apt
int parse_and_set_get_apartments_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct Command* output);
int parse_get_apartments_command_arguments_to_array(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, char** output);
int parse_and_set_apartments_command_arguments_from_array(char** parameters, size_t number_of_parameters, struct GetApartmentsCommand* output);
int parse_and_set_apartments_command_int_arguments_by_name_and_value(char* parameter_name, char* parameter_value, struct GetApartmentsCommand* output);

//The only public method in parser. Translate the string command (from the console) to struct Command.
int parse_command (char* input, size_t input_max_length, struct Command* p_output) {
	//variables
	int result = 0;
	size_t number_of_arguments = 0;
	size_t *arguments_index = NULL;

	//Count the number of arguments in the input command string, and the index of the ast char of each argument.
	number_of_arguments = count_arguments_in_command_line(input, input_max_length) + 1;
	arguments_index = (size_t*)malloc(sizeof(size_t)*(number_of_arguments+1));
	error_if_condition_true_print_and_exit((arguments_index == NULL), "malloc return NULL on 'arguments_index' in 'parser.c'");
	arguments_index[number_of_arguments] = '\0';
	result = arguments_index_in_command_line(input, input_max_length, arguments_index, number_of_arguments);
	if (result != METHOD_SUCCESS) {
		free(arguments_index);
		return METHOD_FAILURE;
	}

	//Find the type of the command: add-an-apt, get-an-apt, buy-an-apt, delete-an-apt, ...
	result =  set_command_type(input, input_max_length, arguments_index, p_output);
	if (result != METHOD_SUCCESS) {
		free(arguments_index);
		return METHOD_FAILURE;
	}

	//Set all the struct commend arguments based on the command type and the arguments in the input string.
	result =  parse_and_set_command_arguments(input, input_max_length, arguments_index, number_of_arguments, p_output);
	if (result != METHOD_SUCCESS) {
		free(arguments_index);
		return METHOD_FAILURE;
	}
	//Free the memory we malloc in this method. In c we must free after every malloc to prevent memory leaks!
	free(arguments_index);
	return result;
}

//Private methods used only by the public method parse_command. But for every command from any type.
size_t count_arguments_in_command_line(char* input, size_t input_max_length) {
	size_t i = 0, k = 0, count = 0;
	int inner_loop = 1, outer_loop = 1;
	char c = 0;
	for (i = 0; i<input_max_length && outer_loop; i++) {
		c = input[i];
		if (c == '\0') {
			outer_loop = 0;
		}
		if (c == ' ') {
			count++;
		}
		if (c == '"') {
			for (i = i+1; i < input_max_length && inner_loop; i++) {
				c = input[i];
				if (c == '\0') {
					outer_loop = 0;
				}
				if (c == '"') {
					inner_loop = 0;
				}
			}
			i = i - 1;
		}
	}
	return 	count;
}

int arguments_index_in_command_line(char* input, size_t input_max_length, size_t* output, size_t output_length) {
	size_t i = 0, arguments_index = 0;
	int inner_loop = 1, outer_loop = 1;
	char c = 0;
	for (i = 0; i<input_max_length && outer_loop; i++) {
		c = input[i];
		if (c == '\0') {
			output[arguments_index] = i - 1;
			outer_loop = 0;
		}
		if ((c == ' ') || (c == '\n')) {
			output[arguments_index] = i - 1;
			arguments_index++;
			if (arguments_index>output_length) {
				return METHOD_FAILURE; //error
			}
		}
		if (c == '"') {
			for (i = i + 1; i < input_max_length && inner_loop; i++) {
				c = input[i];
				if (c == '\0') {
					outer_loop = 0;
				}
				if (c == '"') {
					inner_loop = 0;
				}
			}
			i = i - 1;
		}
	}
	return 	METHOD_SUCCESS;
}

int set_command_type(char* input, size_t input_max_length, size_t* index_array, struct Command* p_output) {
	int result = 0;
	size_t command_name_length = index_array[0]+1; //index start from zero.
	char *command_name = malloc(sizeof(char)*(command_name_length+1));
	error_if_condition_true_print_and_exit((command_name == NULL), "malloc return NULL on 'command_name' in 'parser.c'");
	command_name[command_name_length] = '\0';
	result = strncpy_s(command_name, command_name_length+1, input, command_name_length);
	if (result!= METHOD_SUCCESS) {
		return METHOD_FAILURE;
	}
	p_output->type = get_command_type_by_command_name(command_name);
	free(command_name);
	return result;
}

enum CommandType get_command_type_by_command_name(char* command_name) {
	if (strcmp(command_name, "add-an-apt") == 0) {
		return CommandTypeAddApartment;
	}
	if (strcmp(command_name, "buy-an-apt") == 0) {
		return CommandTypeBuyApartment;
	}
	if (strcmp(command_name, "delete-an-apt") == 0) {
		return CommandTypeDeleteApartment;
	}
	if (strcmp(command_name, "get-an-apt") == 0) {
		return CommandTypeGetApartments;
	}
	if (strcmp(command_name, "exit") == 0) {
		return CommandTypeAddExit;
	}
	return CommandTypeUnknown;
}

int parse_and_set_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct Command* p_output) {
	if (p_output->type == CommandTypeAddApartment) {
		parse_and_set_add_apartment_command_arguments(input, input_max_length, index_array, index_array_length, p_output);
		return METHOD_SUCCESS;
	}
	if (p_output->type == CommandTypeBuyApartment) {
		parse_and_set_buy_apartment_command_arguments(input, input_max_length, index_array, index_array_length, p_output);
		return METHOD_SUCCESS;
	}
	if (p_output->type == CommandTypeDeleteApartment) {
		return METHOD_SUCCESS;
	}
	if (p_output->type == CommandTypeGetApartments) {
		//TODO: uncomment
		parse_and_set_get_apartments_command_arguments(input, input_max_length, index_array, index_array_length, p_output);
		return METHOD_SUCCESS;
	}
	if (p_output->type == CommandTypeAddExit) {
		return METHOD_SUCCESS;
	}
	if (p_output->type == CommandTypeUnknown) {
		return METHOD_SUCCESS;
	}
	return METHOD_FAILURE;
}

//Private methods used only by the public method parse_command. And each method is use for only on type of command.
int parse_and_set_add_apartment_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct Command* p_output) {
	int result = 0;
	if (index_array_length!=7) {
		return METHOD_FAILURE; //Wrong number of arguments for this command.
	}
	struct AddApartmentCommand* arguments = NULL;
	arguments = (struct AddApartmentCommand*)malloc(sizeof(struct AddApartmentCommand));
	error_if_condition_true_print_and_exit((arguments == NULL), "malloc return NULL on 'arguments' in 'parser.c'");

	//Calculate address index in input without quotation marks.
	size_t address_quotation_index_1 = index_array[0]+2;
	size_t address_quotation_index_2 = index_array[1];
	size_t address_start_index = address_quotation_index_1 + 1;
	size_t address_end_index = address_quotation_index_2 - 1;
	//set address_size and address
	arguments->address_size = address_end_index - address_start_index + 2; //+1 for zero index and +1 for '\n'
	arguments->address = (char*)malloc(sizeof(char)*arguments->address_size);
	result = strncpy_s(arguments->address, arguments->address_size+1, input+ address_start_index, arguments->address_size);
	if (result != 0) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->address[arguments->address_size-1] = '\0';
	//set all other numeric values of add command
	char *p_char_after_number;
	long long_from_string;
	//price
	long_from_string = strtol(input+index_array[1]+2, &p_char_after_number, 10);
	if (*p_char_after_number != ' ' ||  long_from_string < 0 || long_from_string > INT_MAX) {
		return METHOD_FAILURE;
	}
	arguments->price = (int)long_from_string;

	//number_of_rooms
	long_from_string = strtol(input + index_array[2] + 2, &p_char_after_number, 10);
	if (*p_char_after_number != ' ' || long_from_string < 0 || long_from_string > INT_MAX) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->number_of_rooms = (int)long_from_string;

	//day
	long_from_string = strtol(input + index_array[3] + 2, &p_char_after_number, 10);
	if (*p_char_after_number != ' ' || long_from_string < 0 || long_from_string > INT_MAX) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->day = (int)long_from_string;

	//month
	long_from_string = strtol(input + index_array[4] + 2, &p_char_after_number, 10);
	if (*p_char_after_number != ' ' || long_from_string < 0 || long_from_string > INT_MAX) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->month = (int)long_from_string;

	//year
	long_from_string = strtol(input + index_array[5] + 2, &p_char_after_number, 10);
	int is_invalid_char = (*p_char_after_number != ' ') && (*p_char_after_number != '\n') && (*p_char_after_number != '\0');
	if (is_invalid_char || long_from_string < 0 || long_from_string > INT_MAX) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->year = (int)long_from_string;

	p_output->arguments = arguments;

	return METHOD_SUCCESS;
}

int parse_and_set_buy_apartment_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct Command* output) {
	int result = 0;
	if (index_array_length != 2) {
		return METHOD_FAILURE; //Wrong number of arguments for this command.
	}
	struct BuyApartmentCommand* arguments = NULL;
	arguments = (struct BuyApartmentCommand*)malloc(sizeof(struct BuyApartmentCommand));
	error_if_condition_true_print_and_exit((arguments == NULL), "malloc return NULL on 'arguments' in 'parser.c'");

	char *p_char_after_number;
	long long_from_string;
	long_from_string = strtol(input + index_array[0]+2, &p_char_after_number, 10);
	bool invalid_next_char = (*p_char_after_number != '\n') && (*p_char_after_number != ' ');
	if (*p_char_after_number != '\n' || long_from_string < 0 || long_from_string > INT_MAX) {
		return METHOD_FAILURE;
	}
	arguments->code = (int)long_from_string;
	output->arguments = arguments;
	return METHOD_SUCCESS;
}

int parse_and_set_get_apartments_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct Command* output) {
	//Read params from input to a parameters 2d array
	char** parameters = (char**)malloc(sizeof(char*)*index_array_length);
	parameters[index_array_length-1] = '\0';
	parse_get_apartments_command_arguments_to_array(input, input_max_length, index_array, index_array_length, parameters);

	//Read params from parameters 2d array to struct GetApartmentsCommand* arguments
	struct GetApartmentsCommand* arguments = NULL;
	arguments = (struct GetApartmentsCommand*)malloc(sizeof(struct GetApartmentsCommand));
	error_if_condition_true_print_and_exit((arguments == NULL), "malloc return NULL on 'arguments' in 'parser.c'");
	parse_and_set_apartments_command_arguments_from_array(parameters, (index_array_length - 1), arguments);
	output->arguments = arguments;
	
	//Free the memory we malloc in this method. In c we must free after every malloc to prevent memory leaks!
	for (int i = 0; i < index_array_length; i++) {
		free(parameters[i]);
	}
	return METHOD_SUCCESS;
}

int parse_get_apartments_command_arguments_to_array(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, char** output) {
	int number_of_parameters = index_array_length - 1;
	for (int i = 0; i < number_of_parameters; i++) {
		int argument_length = index_array[i + 1] - index_array[i];
		output[i] = (char*)malloc(sizeof(char)*argument_length);
		error_if_condition_true_print_and_exit((output[i] == NULL), "malloc return NULL on 'arguments->parameters[i]' in 'parser.c'");
		int result = strncpy_s(output[i], argument_length, input + index_array[i] + 2, argument_length - 1);
		if (result != 0) {
			//free(arguments->address);
			//TODO 
			return METHOD_FAILURE;
		}
		output[i][argument_length - 1] = '\0';
	}
	return METHOD_SUCCESS;
}

int parse_and_set_apartments_command_arguments_from_array(char** parameters, size_t number_of_parameters, struct GetApartmentsCommand* output) {
	command_init_get_apartments_command(output);
	for (size_t i = 0; i < number_of_parameters; i++) {
		char* parameter_name = parameters[i];
		if (i < (number_of_parameters - 1)) {
			int result = parse_and_set_apartments_command_int_arguments_by_name_and_value(parameter_name, parameters[i + 1], output);
			if (result!= METHOD_SUCCESS) {
				return METHOD_FAILURE;
			}
		}
		if (strcmp(parameter_name, "-s") == 0) {
			output->sort_type = SortTypeByPriceLowToHigh;
		}
		if (strcmp(parameter_name, "-sr") == 0) {
			output->sort_type = SortTypeByPriceHighToLow;
		}
	}
	return METHOD_SUCCESS;
}

int parse_and_set_apartments_command_int_arguments_by_name_and_value(char* parameter_name, char* parameter_value, struct GetApartmentsCommand* output) {
	char *p_char_after_number;
	long long_from_string;
	if (strcmp(parameter_name, "-MinimumNumRooms") == 0) {
		long_from_string = strtol(parameter_value, &p_char_after_number, 10);
		if (long_from_string < 0 || long_from_string > INT_MAX) {
			return METHOD_FAILURE;
		}
		output->min_rooms = (int)long_from_string;
	}
	if (strcmp(parameter_name, "-MaximumNumRooms") == 0) {
		long_from_string = strtol(parameter_value, &p_char_after_number, 10);
		if (long_from_string < 0 || long_from_string > INT_MAX) {
			return METHOD_FAILURE;
		}
		output->max_rooms = (int)long_from_string;
	}
	if (strcmp(parameter_name, "–MinimumPrice") == 0) {
		long_from_string = strtol(parameter_value, &p_char_after_number, 10);
		if (long_from_string < 0 || long_from_string > INT_MAX) {
			return METHOD_FAILURE;
		}
		output->min_price = (int)long_from_string;
	}
	if (strcmp(parameter_name, "-MaximumPrice") == 0) {
		long_from_string = strtol(parameter_value, &p_char_after_number, 10);
		if (long_from_string < 0 || long_from_string > INT_MAX) {
			return METHOD_FAILURE;
		}
		output->max_price = (int)long_from_string;
	}
	return METHOD_SUCCESS;
}