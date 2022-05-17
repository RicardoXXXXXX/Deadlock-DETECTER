#ifndef _PROCESS_DATA_H
#define _PROCESS_DATA_H
#include "detect.h"
cluster_t* init_cluster();
node_t* new_node(cluster_t* cluster, unsigned int input_id, int input_type);
int process_file(char* file_name, cluster_t* cluster);
node_t* is_node_exit(cluster_t* cluster, unsigned int input_id, int input_type);
void store_node(cluster_t* cluster, node_t* new_node);
void display_file_process_quantity(cluster_t* cluster);
int max_repeat_times(int A[], int n);
node_t** read_store_data_task6(char* file_name);
int file_len(char* file_name);
node_t* new_node_task6(unsigned int input_id, int input_type);
#endif
