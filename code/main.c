#include "ui.h"
#include "parser.h"
#include "commands.h"

#define MAX_LINE_LENGTH 1024

int main()
{
	int result = 0;
	size_t line_max_length = 1024;
	char *line = malloc(sizeof(char)*line_max_length);
	struct command* p_command = malloc(sizeof(struct command));
	ui_welcome_message();
	result = ui_read_command(line, line_max_length);
	if (result<0) {
		return -1;
	}
	result =  parse_command(line, line_max_length, p_command);
	if (result<0) {
		return -1;
	}
	free(line);
	getchar();
	return result;
}