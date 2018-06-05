#ifndef PARSER_H_
#define PARSER_H_

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "errors.h"

#define INT_MAX       2147483647 //In case it is not define

//The only public method in parser. Translate the string command (from the console) to struct Command.
int parse_command(char* line, size_t line_max_length, struct Command* p_output);

#endif