/**
 * @file file.h
 * @brief 
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _FILE_H_
#define _FILE_H_

/*Import System Files*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/*Import Local Files*/
#include "array.h"
#include "graph.h"
#include "heap.h"
#include "dijkstra.h"

const char *file_extention(const char* file_name);
FILE* output_file(char* file_name);
void write_output(FILE* fp, char* first_word, char* last_word, int n, int n_result1, int n_result2);
//void Problem_file_2(char** main_array[], int* counter, FILE* fPtr, FILE* fp_out);
void Problem_file(char** main_array[],int* counter, FILE* fPtr, FILE* fp_out, Graph* graphs[46]);
void printSolution(FILE* fp, int src, int i, int* dist, int* parents, int V, char** mainArr);
void printArr(int dist[], int n);

#endif