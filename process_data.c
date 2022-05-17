#include "process_data.h"

//Read file and store data into the cluster
int process_file(char *file_name, cluster_t *cluster) {
    unsigned int process_id, lock_file_id, request_file_id;
    int line_quantity = 0;
    int max_repeat_time = 0;    //Appearing quantitiy of most common request node
    int* request_nodes = malloc(sizeof(int) * MAXNODES);  //Create a node array
    node_t* process_node, * lock_node, * request_node;
    FILE* fp = fopen(file_name, "r");

    //Check if the file address is empty
    if (fp == NULL) {
        printf("No file has been input\n");
        exit(EXIT_FAILURE);
    }

    //Read date from the file
    while (fscanf(fp, "%u%u%u", &process_id, &lock_file_id, &request_file_id) == 3) {
        process_node = new_node(cluster, process_id, TYPE_PROCESS);
        lock_node = new_node(cluster, lock_file_id, TYPE_LOCK_FILE);
        request_node = new_node(cluster, request_file_id, TYPE_REQUEST_FILE);
        
        //Connect process with files
        lock_node->next = process_node;
        process_node->next = request_node; 
        
        //Double space if current array is full
        if (line_quantity == MAXNODES) {
            request_nodes = (int *)realloc(request_nodes, 2* line_quantity * sizeof(int));
        }
        //Add request node to node array
        request_nodes[line_quantity] = request_file_id;
        line_quantity++;
    }
    //Find the quantitiy of most common request node
    max_repeat_time = max_repeat_times(request_nodes, line_quantity);

    //fclose(fp); //Close the file.
    free(request_nodes); //Free memory
    return max_repeat_time;
}

//Create a new empty cluster
cluster_t *init_cluster() {
    cluster_t *cluster = malloc(sizeof(cluster_t));
    cluster->node_array = malloc(MAXNODES * sizeof(node_t*));
    cluster->node_quantity = 0;
    cluster->lock_file_quantity = 0;
    cluster->request_file_quantity = 0;
    cluster->process_quantity = 0;
    cluster->max_size = MAXNODES;

    return cluster;
}

//return the adress of a new node or existed node
node_t *new_node(cluster_t *cluster, unsigned int input_id, int input_type) {
    node_t *new_node;

    //If this node already in the cluster, return its address
    if ((new_node = is_node_exit(cluster, input_id, input_type)) != NULL) {
        return new_node;
    }
    //Else, create a new ndoe
    new_node = malloc(sizeof(node_t));
    new_node->id = input_id;
    new_node->next = NULL;
    new_node->is_test = NO;
    new_node->is_used = NO;
    if (input_type == TYPE_LOCK_FILE || input_type == TYPE_REQUEST_FILE) {
        new_node->type = TYPE_FILE;
        new_node->file_type = input_type;
    }
    else {
        new_node->type = TYPE_PROCESS;
        new_node->file_type = NO;
    }

    //Store the node
    store_node(cluster, new_node);

    //Count process and file quantity
    if (new_node->type == TYPE_PROCESS) {

        cluster->process_quantity++;
    }
    else if (new_node->type == TYPE_FILE && new_node->file_type == TYPE_LOCK_FILE) {
        cluster->lock_file_quantity++;
    }
    else if (new_node->type == TYPE_FILE && new_node->file_type == TYPE_REQUEST_FILE) {
        cluster->request_file_quantity++;
    }
    return new_node;
}

void store_node(cluster_t *cluster, node_t *new_node) {
    //Add more space if the current node array is full
    if (cluster->node_quantity >= cluster->max_size) {
        cluster->max_size *= 2;
        cluster->node_array = (node_t**)realloc(cluster->node_array, (cluster->max_size) * sizeof(node_t*));
    }
    //Store node into the cluster
    cluster->node_array[cluster->node_quantity] = new_node;
    cluster->node_quantity++;
}


//Check if the input node already exits
node_t* is_node_exit(cluster_t *cluster, unsigned int input_id, int input_type) {
    int position = 0;
    if (input_type == TYPE_LOCK_FILE || input_type == TYPE_REQUEST_FILE) {
        input_type = TYPE_FILE;
    }

    //If the node array is emoty
    if (cluster->node_quantity == 0) {
        return NULL;
    }
    else { //Go through the cluster
        while (position < cluster->node_quantity) {
            if (input_id == (cluster->node_array[position]->id) 
                && input_type == (cluster->node_array[position]->type)) {
                return cluster->node_array[position];
            }
            position++;
        }
        return NULL;
    }
}

//Display the quantity of files and processes
void display_file_process_quantity(cluster_t *cluster) {
    printf("Processes %u\n", cluster->process_quantity);
    printf("Files %u\n", cluster->request_file_quantity + cluster->lock_file_quantity);
}


//This function find the frequency of the most common element of input array
int max_repeat_times(int A[], int n) {
    int i, j, max = 0, count;
    for (i = 0; i < n; i++) {
        // find frequency of A[i] in rest of array
        count = 0;
        for (j = i; j < n; j++) {
            if (A[i] == A[j]) {
                count++;
            }
        }
        // and if this greatest frequency so far, record it
        if (count > max) {
            max = count;
        }
    }
    return max;
}

//Read date from the task6 file
node_t** read_store_data_task6(char* file_name) {
    node_t** process_array = malloc(MAXNODES * sizeof(node_t*));
    unsigned int process_id, lock_file1_id, lock_file2_id;
    node_t* process_node, * lock1_node, * lock2_node;
    int file_line_num = 0;
    FILE* fp = fopen(file_name, "r");

    //Check if the file address is empty
    if (fp == NULL) {
        printf("No file has been input\n");
        exit(EXIT_FAILURE);
    }

    //Read date from the file, store them in nodes
    while (fscanf(fp, "%u%u%u", &process_id, &lock_file1_id, &lock_file2_id) == 3) {
        process_node = new_node_task6(process_id, TYPE_PROCESS);
        lock1_node = new_node_task6(lock_file1_id, TYPE_FILE);
        lock2_node = new_node_task6(lock_file2_id, TYPE_FILE);

        //Connect process with files
        process_node->next = lock1_node;
        lock1_node->next = lock2_node;
        //Store them into process array
        process_array[file_line_num] = process_node;
        file_line_num++;
    }
    return process_array;
}

//Create a new node, return its address
node_t* new_node_task6(unsigned int input_id, int input_type) {
    node_t* new_node;
    //Create a new ndoe
    new_node = malloc(sizeof(node_t));
    new_node->id = input_id;
    new_node->next = NULL;
    new_node->is_test = NO;
    if (input_type == TYPE_FILE) {
        new_node->is_used = YES;
    }
    else
    {
        new_node->is_used = NO;
    }
    new_node->type = input_type;
    new_node->file_type = NO_EXIST;

    return new_node;
}

//Rturn the line_num of file
int file_len(char* file_name) {
    int file_line_num = 0;
    FILE* fp = fopen(file_name, "r");
    unsigned int process_id = 0, lock_file1_id = 0, lock_file2_id = 0;
    while (fscanf(fp, "%u%u%u", &process_id, &lock_file1_id, &lock_file2_id) == 3) {
        file_line_num++;
    }
    return file_line_num;
}
