#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "errors.h"

#define INT_MAX       2147483647 //In case it is not define

int parse_command(char* line, size_t line_max_length, struct command* result);

#endif