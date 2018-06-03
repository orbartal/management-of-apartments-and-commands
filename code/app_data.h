#ifndef APP_DATA_H_
#define APP_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "apartments.h"


typedef struct AppDATA
{
	int last_apartment_code;
	struct LinkedList* apartments;
}AppDATA;

int app_data_init(struct AppDATA* p_app_data);
int app_data_free(struct AppDATA* p_app_data);

#endif