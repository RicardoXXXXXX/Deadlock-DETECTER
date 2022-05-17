#include "process_deadlock.h"

//Check if deadlock exits
int is_deadlock(cluster_t* cluster) {
	int result = 0;
	//Go through this cluster
	for (int i = 0; i < cluster->node_quantity; i++) {
		if (cluster->node_array[i]->type == TYPE_PROCESS) {
			if ((result = is_node_in_deadlock(cluster->node_array[i]))) {
				//Refresh node usage
				format_nodes_usage(cluster);
				return YES;
			}
		}
	}
	//Refresh node usage
	format_nodes_usage(cluster);
	return NO;
}

//Check if the input node is in deadlock
int is_node_in_deadlock(node_t* node) {
	node_t* start_node = node;
	node_t* current_node = node->next;
	
	//Go through the node's following nodes
	while (current_node->next != NULL) {
		//Back to the start, this node is in a circle
		if ((current_node->id == start_node->id && current_node->type == start_node->type)
			//Fall in infinite loop, this node is connected with a circle
			|| current_node->is_used) {
			return YES;
		}
		//Mark the current node as used
		current_node->is_used = YES;
		current_node = current_node->next;
	}
	return NO;
}

//Display the deadlock information
void display_deadlock_result(cluster_t* cluster, int max_repeat_time, int show_time) {
	//Deadlock detected
	if (is_deadlock(cluster)) {
		//init an array to store nodes in a deadlock
		node_t** terminated_nodes_array = malloc(cluster->node_quantity * sizeof(node_t*));
		printf("Deadlock detected\n");
		//Find the number of terminate processes
		int num_terminated_process = terminated_node_array(cluster, terminated_nodes_array);
		//Sort the array in low->high order
		sort_node_array(terminated_nodes_array, num_terminated_process);
		printf("Terminate");
		for (int i = 0; i < num_terminated_process; i++) {
			printf(" %u", terminated_nodes_array[i]->id);
		}
		printf("\n");			
		free(terminated_nodes_array);	//Free memory
	}
	else // No deadlock
	{	
		if(show_time){
			printf("No deadlocks\n");
			display_execution_time(max_repeat_time);
		}else{
			printf("No deadlocks\n");
		}
	}
}

//Display task 2 result
void display_execution_time(int max_repeat_time) {
	printf("Execution time %u\n", max_repeat_time);
}

//Add the terminated nodes into a list, return its length
int terminated_node_array(cluster_t* cluster, node_t **terminated_nodes_array) {
	int array_len = 0;
	node_t *min_process_node;

	//Loop the cluster, find the terminated processes.
	for (int i = 0; i < cluster->node_quantity; i++) {
		node_t* current_node = cluster->node_array[i];
		//Find a process that never been checked before
		if (current_node->type == TYPE_PROCESS && current_node->is_test == NO) {
			//This process is in a circle
			if (is_node_in_circle(current_node)) {
				//Find the min process id in this circle
				min_process_node = detect_terminated_process(current_node);
				terminated_nodes_array[array_len] = min_process_node;
				array_len++;
			}
		}
		//refresh node usage
		format_nodes_usage(cluster);
	}
	return array_len;
}

//Refresh all nodes' usage
void format_nodes_usage(cluster_t *cluster) {
	for (int i = 0; i < cluster->node_quantity; i++) {
		cluster->node_array[i]->is_used = NO;
	}
}

//Find the min process in a deadlock
node_t *detect_terminated_process(node_t *node) {
	node_t *min_process_node = node;
	node_t *current_node = node;
	while (current_node->next != node) {
		//Assign min-process_node with a node that has a smaller id 
		if (current_node->id < min_process_node->id && current_node->type == TYPE_PROCESS) {
			min_process_node = current_node;
		}
		//Mark tested node, avoid re-test
		current_node->is_test = YES;
		current_node = current_node->next;
	 }
	return min_process_node;
}

//Detect if a input process node is in a circle
int is_node_in_circle(node_t *node) {
	node_t* start_node = node;
	node_t* current_node = node;

	//Go through the following nodes
	while (current_node->next != NULL) {
		current_node->is_used = YES;
		current_node = current_node->next;
		//Back to the start, this node is in a circle
		if (current_node->id == start_node->id && current_node->type == start_node->type) {
			return YES;
		}
		/*Back to a tested node, this node is out of the circle
		but in a deadlock*/
		else if (current_node->is_used == YES) {
			return NO;
		}
	}
	return NO;
}

//Sort the node array in 
void sort_node_array(node_t **terminated_nodes_array, int len) {
	int i, j;
	// assume that A[0] to A[n-1] have valid values
	for (i = 1; i < len; i++) {
		// swap node left into correct position
		for (j = i - 1; j >= 0 
			&& terminated_nodes_array[j + 1]->id < terminated_nodes_array[j]->id; j--) {
			id_swap(terminated_nodes_array[j], terminated_nodes_array[j + 1]);
		}
	}

	
}

//Swap input node's id
void id_swap(node_t *n1, node_t *n2) {
	int tmp_id;
	tmp_id = n1->id;
	n1->id = n2->id;
	n2->id = tmp_id;
}

//Shedule no-deadlock process in the same time
void detect_exeucte_process_order(node_t** process_array, int process_num) {
	int execute_time = 0;	//Exe time
	int count = 0;	//How many process has been picked
	int array_len = 0;	//Len of current_processes
	int simulation_time = NO_EXIST;
	node_t** current_processes = malloc(sizeof(int*) * process_num);
	node_t* one_process;

	//Sheduling start
	while (count != process_num) {
		//Refresh the current node
		array_len = 0;
		//Check if a node is available in current time
		while ((one_process = detect_one_process(current_processes, process_array, array_len, process_num)) != NULL) {
			current_processes[array_len] = one_process; 
			array_len++;
		}
		//All noded in the same time have been founded, print
		for (int i = 0; i < array_len; i++) {
			if (execute_time != simulation_time) {
				simulation_time++;
			}
			printf("%u %u %u %u\n", execute_time, current_processes[i]->id, 
				current_processes[i]->next->id, current_processes[i]->next->next->id);
		}
		//Another round
		execute_time++;
		count++;
	}
	if (count == process_num) {
		printf("Simulation time %u\n", simulation_time + 1);
	}
	free(current_processes); //Free memory
}

//Pick one availabe node from process array, add it into current process array
node_t* detect_one_process(node_t** current_processes, node_t** process_array, int array_len, int process_num) {
	node_t* process = malloc(sizeof(node_t));
	//When the current node is empty, add the first available node
	if (array_len == 0) {
		for (int i = 0; i < process_num; i++) {
			if (process_array[i] != NULL) {
				process = process_array[i];
				//current_processes[array_len] = process;
				array_len++;
				process_array[i] = NULL;
				return process;
			}
		}
	}
	//Loop the process array, find availabe node
	for (int i = 0; i < process_num; i++) {
		if (process_array[i] != NULL) {
			if (is_file_in_current_processes(current_processes, 
				process_array[i], array_len) == NO) {
				process = process_array[i];
				//Add into the current node
				current_processes[array_len] = process;
				array_len++;
				process_array[i] = NULL;
				return process;
			}
		}
	}
	//Checking finishs, return NULL
	process = NULL;
	return process;
}

//Check if the input node has same file with other nodes in current array
int is_file_in_current_processes(node_t** current_processes, node_t* process, int len) {
	int input_lock1 = process->next->id;
	int input_lock2 = process->next->next->id;

	//Loop the current process array, check if any file id macths
	for (int i = 0; i < len; i++) {
		int check_lock1 = current_processes[i]->next->id;
		int check_lock2 = current_processes[i]->next->next->id;
		//Find macthed files, return YES
		if (input_lock1 == check_lock1 || input_lock1 == check_lock2
			|| input_lock2 == check_lock1 || input_lock2 == check_lock2) {
			return YES;
		}
	}
	//Finish checking, no macthed file detected
	return NO;
}
