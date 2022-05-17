#ifndef _DETECT_H
#define _DETECT_H
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TYPE_PROCESS 0
#define TYPE_FILE 1
#define TYPE_LOCK_FILE 2
#define TYPE_REQUEST_FILE 3
#define YES 1
#define NO 0
#define MAXNODES 1000
#define MAXLINES 1000
#define NO_EXIST -1

typedef struct node node_t;
struct node {
    unsigned int id;
    int type;
    int file_type;
    int is_test;
    int is_used;
    node_t *next;
};

typedef struct {
    node_t **node_array;    //Array of nodes
    int node_quantity;  ////Unique nodes
    int process_quantity; //Unique processs
    int lock_file_quantity;   //Unique files
    int request_file_quantity; 
    int max_size;
}cluster_t;


#endif
