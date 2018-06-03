#include "apartments.h"

void apartments_list_init(struct aptList* apartments) {
	apartments->head = NULL;
	apartments->tail = NULL;
}

void apartments_list_free(struct aptList* apartments) {
	//TODO
}

void apartments_print_one(struct apt* input) {
	printf("\napartments_print_one:\n");
	printf("\naddress_code is %d\n", input->code);
	printf("\naddress_size is %d\n", input->address_size);
	printf("\naddress is %s\n", input->address);
	printf("\nprice is %d\n", input->price);
	printf("\nnumberOfRooms is %d\n", input->number_Of_rooms);
	printf("\nday is %d\n", input->day);
	printf("\nmonth is %d\n", input->month);
	printf("\nyear is %d\n", input->year);
}