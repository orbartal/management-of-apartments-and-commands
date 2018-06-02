#include "ui.h"

#define MAX_LINE_LENGTH 1024

int main()
{
	size_t line_max_length = 1024;
	char *line = malloc(sizeof(char)*line_max_length);
	ui_welcome_message();
	ui_read_command(line, line_max_length);
	free(line);
	getchar();
	return 0;
}