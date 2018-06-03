#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>
#include <stdlib.h>

#define METHOD_SUCCESS EXIT_SUCCESS
#define METHOD_FAILURE EXIT_FAILURE

void error_if_condition_true_print_and_exit(int condition, char* p_message);

#endif

