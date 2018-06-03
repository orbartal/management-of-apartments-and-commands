#ifndef APP_DATA_H_
#define APP_DATA_H_

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "apartments.h"


typedef struct appDATA
{
	struct apt* apt_temp; //TODO: remove
	int last_apartment_code;
	struct LinkedList* apartments;
}appDATA;

int app_data_init(struct appDATA* p_app_data);
int app_data_free(struct appDATA* p_app_data);

#endif