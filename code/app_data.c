#include "app_data.h"

int app_data_init(struct AppDATA* p_app_data) {
	p_app_data->last_apartment_code = 0;
	p_app_data->apartments = malloc(sizeof(LinkedList));
	error_if_condition_true_print_and_exit((p_app_data->apartments == NULL), "malloc return NULL on 'p_app_data->apartments' in 'app_data.c'");
	list_init_empty(p_app_data->apartments);
	return METHOD_SUCCESS;
}

int app_data_free(struct AppDATA* p_app_data) {
	list_free_list_and_all_nodes_and_data(p_app_data->apartments);
	free(p_app_data);
	return METHOD_SUCCESS;
}