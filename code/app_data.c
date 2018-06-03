#include "app_data.h"

int app_data_init(struct appDATA* p_app_data) {
	p_app_data->apartments = malloc(sizeof(AptList));
	error_if_condition_true_print_and_exit((p_app_data->apartments == NULL), "malloc return NULL on 'p_app_data->apartments' in 'app_data.c'");
	apartments_list_init(p_app_data->apartments);
	return METHOD_SUCCESS;
}

int app_data_free(struct appDATA* p_app_data) {
	apartments_list_free(p_app_data->apartments);
	free(p_app_data);
	return METHOD_SUCCESS;
}