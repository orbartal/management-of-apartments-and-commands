#include "apartments.h"

void apartments_list_init(struct aptList* apartments) {
	apartments->head = NULL;
	apartments->tail = NULL;
}

void apartments_list_free(struct aptList* apartments) {
	//TODO
}