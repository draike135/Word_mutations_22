#ifndef _ARRAY_H_
#define _ARRAY_H_

/*Import System Files*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

char*** array(FILE* fp_dict, char*** main_array,int* counter);
void swap(char** a,char** b);
void quicksort(char* arr[], int length);
int binarySearch(char* input, char* arr[], int l, int r);
char** Main_list(int words, int size_words);
void free_array(char* arr[], int n);
void free_all(char** main[], int* counter);

#endif