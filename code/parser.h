#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

int parse_command(char* line, size_t line_max_length, struct command* result);

#endif