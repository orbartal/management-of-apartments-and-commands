#include "app_data.h"
#include "ui.h"
#include "parser.h"
#include "commands.h"

#define MAX_LINE_LENGTH 1024

int main()
{
	int result = 0;
	size_t line_max_length = 1024;

	AppDATA* p_app_data = malloc(sizeof(AppDATA));
	error_if_condition_true_print_and_exit((p_app_data == NULL), "malloc return NULL on 'p_app_data' in 'main.c'");
	app_data_init(p_app_data);

	char *p_line = malloc(sizeof(char)*line_max_length);
	error_if_condition_true_print_and_exit((p_line == NULL), "malloc return NULL on 'p_line' in 'main.c'");
	struct Command* p_command = malloc(sizeof(struct Command));
	error_if_condition_true_print_and_exit((p_line == NULL), "malloc return NULL on 'p_command' in 'main.c'");

	ui_welcome_message();

	while (p_command->type!= CommandTypeAddExit) {
		result = ui_read_command(p_line, line_max_length);
		error_if_condition_true_print_and_exit((result != METHOD_SUCCESS), "method ui_read_command return -1. called from 'main.c'");
		
		result = parse_command(p_line, line_max_length, p_command);
		error_if_condition_true_print_and_exit((result != METHOD_SUCCESS), "method parse_command return -1. called from 'main.c'");
		if (p_command->type== CommandTypeUnknown) {
			ui_warning_message("Did not execute unknwon command");
			continue;
		}
		command_execute(p_app_data, p_command);
	}
	free(p_line);
	command_free(p_command);
	app_data_free(p_app_data);
	getchar();
	return EXIT_SUCCESS;
}