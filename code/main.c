#include "ui.h"
#include "parser.h"
#include "commands.h"

#define MAX_LINE_LENGTH 1024

int main()
{
	int result = 0;
	size_t line_max_length = 1024;

	char *line = malloc(sizeof(char)*line_max_length);
	error_if_condition_true_print_and_exit((line == NULL), "malloc return NULL on 'line' in 'main.c'");
	struct command* p_command = malloc(sizeof(struct command));
	error_if_condition_true_print_and_exit((line == NULL), "malloc return NULL on 'p_command' in 'main.c'");

	ui_welcome_message();
	result = ui_read_command(line, line_max_length);
	error_if_condition_true_print_and_exit((result != METHOD_SUCCESS), "method ui_read_command return -1. called from 'main.c'");

	result =  parse_command(line, line_max_length, p_command);
	error_if_condition_true_print_and_exit((result != METHOD_SUCCESS), "method parse_command return -1. called from 'main.c'");

	command_print(p_command);
	command_free(p_command);
	free(line);
	getchar();
	return EXIT_SUCCESS;
}