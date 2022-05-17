#include "process_deadlock.h"
#include "process_data.h"
#include <unistd.h>

int main(int argc, char **argv) {
    char* file_name = NULL;
    char* file_name1 = NULL;
    int show_exe_time = NO;
    //Display diffrent codes based on input sign
    if(strcmp(argv[1], "-f") == 0){
        file_name = argv[2];
        if(argc == 4 && strcmp(argv[3], "-e") == 0){
            show_exe_time = YES;
        }
    } else if(strcmp(argv[2], "-f") == 0){
        file_name = argv[3];
        if(strcmp(argv[1], "-e") == 0){
            show_exe_time = YES;
        }
    }
    //Task6
    if(argc == 4 && strcmp(argv[3], "-c") == 0){
        file_name1 = argv[2];
        node_t** process_array = read_store_data_task6(file_name1);
	    int file_num = file_len(file_name1);
	    detect_exeucte_process_order(process_array, file_num);
    }else if(argc == 4 && strcmp(argv[1], "-c") == 0){
        file_name1 = argv[3];
        node_t** process_array = read_store_data_task6(file_name1);
	    int file_num = file_len(file_name1);
	    detect_exeucte_process_order(process_array, file_num);
    }
    else{//Task1-5
        cluster_t *cluster = init_cluster();   
        int max_repeat_time = 0;
        max_repeat_time = process_file(file_name, cluster)+1;
        display_file_process_quantity(cluster);
        display_deadlock_result(cluster, max_repeat_time, show_exe_time);
        //Free memory
        free(cluster);  
    }
    return 0;
}
