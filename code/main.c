//Includes
#include "app_data.h"
#include "ui.h"
#include "parser.h"
#include "commands.h"

#define MAX_LINE_LENGTH 1024

//Define private methods. Will be used only by methods in this c file. Unknown outside of it.
enum CommandType main_get_one_command_from_user_execute_it_and_return_the_type(AppDATA* p_app_data);
void main_read_parse_and_execute_one_command_from_user(AppDATA* p_app_data, char *p_line, struct Command* p_command);

//The main of the application
int main()
{
	//1. create and intial AppDATA
	AppDATA* p_app_data = malloc(sizeof(AppDATA)); //AppDATA store the global state of the application: departments and commends.
	error_if_condition_true_print_and_exit((p_app_data == NULL), "malloc return NULL on 'p_app_data' in 'main.c'");
	app_data_init(p_app_data);
	//2. Repeatedly read and execute command from user.
	ui_welcome_message();
	enum CommandType command_type_in_loop = CommandTypeUnknown;
	while (command_type_in_loop != CommandTypeAddExit) {
		command_type_in_loop = main_get_one_command_from_user_execute_it_and_return_the_type(p_app_data);
	}
	//3. Free the memory we malloc in this method. In c we must free after every malloc to prevent memory leaks!
	app_data_free(p_app_data);
	return EXIT_SUCCESS;
}

enum CommandType main_get_one_command_from_user_execute_it_and_return_the_type(AppDATA* p_app_data) {
	//1. malloc memory for loop variables.
	char *p_line = malloc(sizeof(char)*MAX_LINE_LENGTH); //cueernt command line from the user console.
	error_if_condition_true_print_and_exit((p_line == NULL), "malloc return NULL on 'p_line' in 'main.c'");
	struct Command* p_command = malloc(sizeof(struct Command)); // The 'p_line' will be parse into 'p_command' and execute.
	error_if_condition_true_print_and_exit((p_line == NULL), "malloc return NULL on 'p_command' in 'main.c'");
	//2. Read parse and execute one_command
	main_read_parse_and_execute_one_command_from_user(p_app_data, p_line, p_command);
	//3. Free the memory we malloc in this method. In c we must free after every malloc to prevent memory leaks!
	enum CommandType type = p_command->type;
	free(p_line);
	command_free(p_command);
	return type;
}

void main_read_parse_and_execute_one_command_from_user(AppDATA* p_app_data, char *p_line, struct Command* p_command) {
	//1. Get command from user.
	int result = ui_read_command(p_line, MAX_LINE_LENGTH);
	error_if_condition_true_print_and_exit((result != METHOD_SUCCESS), "method ui_read_command return -1. called from 'main.c'");
	//2. parse command line string into a struct command with arguments.
	result = parse_command(p_line, MAX_LINE_LENGTH, p_command);
	error_if_condition_true_print_and_exit((result != METHOD_SUCCESS), "method parse_command return -1. called from 'main.c'");
	//3. execute command
	if (p_command->type == CommandTypeUnknown) {
		ui_warning_message("Did not execute unknwon command");
	}
	else {
		command_execute(p_app_data, p_command);
	}
}