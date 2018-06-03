#include "parser.h"

size_t count_arguments_in_command_line(char* input, size_t input_max_length);
int arguments_index_in_command_line(char* input, size_t input_max_length, size_t* output, size_t output_length);
int set_command_type(char* input, size_t input_max_length, size_t* index_array, struct command* output);
int get_command_type_by_command_name(char* command_name);
int parse_and_set_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct command* output);
int parse_and_set_add_app_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct command* output);

int parse_command (char* input, size_t input_max_length, struct command* output) {
	int result = 0;
	size_t *arguments_index = NULL;
	size_t number_of_arguments = count_arguments_in_command_line(input, input_max_length) + 1;

	//printf("There are %d words in the line %s\n", number_of_arguments, input);
	arguments_index = (size_t*)malloc(sizeof(size_t)*(number_of_arguments+1));
	error_if_condition_true_print_and_exit((arguments_index == NULL), "malloc return NULL on 'arguments_index' in 'parser.c'");
	arguments_index[number_of_arguments] = '\0';

	result = arguments_index_in_command_line(input, input_max_length, arguments_index, number_of_arguments);
	if (result != METHOD_SUCCESS) {
		free(arguments_index);
		return METHOD_FAILURE;
	}
/*
	size_t i = 0;
	for (i = 0; i < number_of_arguments; i++) {
		printf("Word %d end in index %d\n", i, arguments_index[i]);
	}
*/
	result =  set_command_type(input, input_max_length, arguments_index, output);
	if (result != METHOD_SUCCESS) {
		free(arguments_index);
		return METHOD_FAILURE;
	}

	result =  parse_and_set_command_arguments(input, input_max_length, arguments_index, number_of_arguments, output);
	if (result != METHOD_SUCCESS) {
		free(arguments_index);
		return METHOD_FAILURE;
	}

	free(arguments_index);
	return result;
}

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

int set_command_type(char* input, size_t input_max_length, size_t* index_array, struct command* output) {
	int result = 0;
	size_t command_name_length = index_array[0]+1; //index start from zero.
	char *command_name = malloc(sizeof(char)*(command_name_length+1));
	error_if_condition_true_print_and_exit((command_name == NULL), "malloc return NULL on 'command_name' in 'parser.c'");
	command_name[command_name_length] = '\0';
	result = strncpy_s(command_name, command_name_length+1, input, command_name_length);
	if (result!= METHOD_SUCCESS) {
		return METHOD_FAILURE;
	}
	//printf("\ncommand name is %s\n", command_name);
	output->type = get_command_type_by_command_name(command_name);
	free(command_name);
	return result;
}

int get_command_type_by_command_name(char* command_name) {
	if (strcmp(command_name, "add-an-apt") == 0) {
		return ADD_APT_COMMAND_TYPE;
	}
	return METHOD_FAILURE;
}

int parse_and_set_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct command* output) {
	if (output->type == ADD_APT_COMMAND_TYPE) {
		parse_and_set_add_app_command_arguments(input, input_max_length, index_array, index_array_length, output);
		return METHOD_SUCCESS;
	}
	return METHOD_FAILURE;
}

int parse_and_set_add_app_command_arguments(char* input, size_t input_max_length, size_t* index_array, size_t index_array_length, struct command* output) {
	int result = 0;
	if (index_array_length!=7) {
		return METHOD_FAILURE; //Wrong number of arguments for this command.
	}
	struct addApartmentCommand* arguments = NULL;
	arguments = (struct addApartmentCommand*)malloc(sizeof(struct addApartmentCommand));
	error_if_condition_true_print_and_exit((arguments == NULL), "malloc return NULL on 'arguments' in 'parser.c'");

	arguments->address_size = index_array[1] - index_array[0] + 1;
	arguments->address = (char*)malloc(sizeof(char)*arguments->address_size);
	result = strncpy_s(arguments->address, arguments->address_size, input+index_array[0] + 1, arguments->address_size-1);
	if (result != 0) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->address[arguments->address_size - 1] = '\0';
	//printf("\naddress is %s\n", arguments->address);

	char *p_char_after_number;
	long long_from_string;
	//price
	long_from_string = strtol(input+index_array[1]+2, &p_char_after_number, 10);
	if (*p_char_after_number != ' ' ||  long_from_string < 0 || long_from_string > INT_MAX) {
		return METHOD_FAILURE;
	}
	arguments->price = (int)long_from_string;
	//printf("\nprice is %d\n", arguments->price);

	//numberOfRooms
	long_from_string = strtol(input + index_array[2] + 2, &p_char_after_number, 10);
	if (*p_char_after_number != ' ' || long_from_string < 0 || long_from_string > INT_MAX) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->numberOfRooms = (int)long_from_string;
	//printf("\nnumberOfRooms is %d\n", arguments->numberOfRooms);

	//day
	long_from_string = strtol(input + index_array[3] + 2, &p_char_after_number, 10);
	if (*p_char_after_number != ' ' || long_from_string < 0 || long_from_string > INT_MAX) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->day = (int)long_from_string;
	//printf("\nday is %d\n", arguments->day);

	//month
	long_from_string = strtol(input + index_array[4] + 2, &p_char_after_number, 10);
	if (*p_char_after_number != ' ' || long_from_string < 0 || long_from_string > INT_MAX) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->month = (int)long_from_string;
	//printf("\nmonth is %d\n", arguments->month);

	//year
	long_from_string = strtol(input + index_array[5] + 2, &p_char_after_number, 10);
	int is_invalid_char = (*p_char_after_number != ' ') && (*p_char_after_number != '\n') && (*p_char_after_number != '\0');
	if (is_invalid_char || long_from_string < 0 || long_from_string > INT_MAX) {
		free(arguments->address);
		free(arguments);
		return METHOD_FAILURE;
	}
	arguments->year = (int)long_from_string;
	//printf("\nyear is %d\n", arguments->year);

	output->arguments = arguments;

	return METHOD_SUCCESS;
}