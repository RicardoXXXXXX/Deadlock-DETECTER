#ifndef _PROCESS_DEADLOCK_H
#define _PROCESS_DEADLOCK_H
#include "detect.h"
int is_deadlock(cluster_t* cluster);
void display_execution_time(int max_repeat_time);
void display_deadlock_result(cluster_t* cluster, int max_repeat_time, int show_time);
int is_node_in_deadlock(node_t* node);
void format_nodes_usage(cluster_t* cluster);
int terminated_node_array(cluster_t* cluster, node_t** terminated_nodes_array);
int is_node_in_circle(node_t* node);
node_t* detect_terminated_process(node_t* node);
void sort_node_array(node_t** terminated_nodes_array, int len);
void id_swap(node_t* n1, node_t* n2);
void detect_exeucte_process_order(node_t** process_array, int process_num);
node_t* detect_one_process(node_t** current_processes, node_t** process_array, int array_len, int process_num);
int is_file_in_current_processes(node_t** current_processes, node_t* process, int len);
#endif
