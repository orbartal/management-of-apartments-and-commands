#include "ui.h"

int ui_welcome_message() {
	printf("Please enter one of the following commands :\n");
	printf("add - an - apt, get - an - apt, buy - an - apt or delete - an - apt\n");
	printf("For reconstruction commands, please enter :\n");
	printf("!!, !num, history, short_history or !num^str1^str2\n");
	printf("To exit, enter exit.\n");
	return METHOD_SUCCESS;
}

int ui_read_command(char* p_line, size_t line_max_length) {
	char *read_result = NULL;
	read_result = fgets(p_line, line_max_length, stdin);
	if (read_result == NULL) {
		return METHOD_FAILURE;
	}
	return METHOD_SUCCESS;
}

int ui_warning_message(char* p_message) {
	printf("%s\n", p_message);
	return METHOD_SUCCESS;
}
