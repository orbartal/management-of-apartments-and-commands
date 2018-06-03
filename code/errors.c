#include "errors.h"

void error_if_condition_true_print_and_exit(int condition, char* p_message) {
	if (condition) {
		printf("Software fail because of error %s\n", p_message);
		exit(EXIT_FAILURE);
	}
}