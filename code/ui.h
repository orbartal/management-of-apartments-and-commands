#ifndef UI_H_
#define UI_H_

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

int ui_welcome_message();
int ui_read_command(char* line, size_t line_max_length);

#endif