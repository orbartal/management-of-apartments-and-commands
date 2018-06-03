#include "errors.h"

void error_if_condition_true_print_and_exit(int condition, char* message) {
	if (condition) {
		printf("Software fail because of error %s\n", message);
		exit(EXIT_FAILURE);
	}
}