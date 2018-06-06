#ifndef UI_H_
#define UI_H_

//Includes
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

//Methods
int ui_welcome_message();
int ui_read_command(char* p_line, size_t line_max_length);
int ui_warning_message(char* p_message);

#endif