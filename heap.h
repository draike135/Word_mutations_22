#ifndef _HEAP_H_
#define _HEAP_H_

/*Import System Files*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/*Import Local Files*/
#include "graph.h"

/*Declare structs*/
typedef struct heap_node HeapNode;
typedef struct heap Heap;

struct heap_node
{
    //destination vertex
	int  v;
    //cost between 2 vertices
	int cost;
};

struct heap
{
    //number of nodes in the heap
	int size;
    //capacity of heap
	int maxSize;
	int* pos;
	HeapNode** array;
};




void swapHeapNode(HeapNode** a, HeapNode** b);
void decreaseKey(Heap* heap, int v, int dist);
void Heapify(Heap* heap, int idx);
int isEmpty(Heap* heap);
Heap* createHeap(int capacity);
HeapNode* newHeapNode(int v, int dist);
HeapNode* extractMinimum(Heap* heap);
bool isInHeap(Heap* heap, int v);
void printPath(FILE* fp, int parent[], int j, char** mainArr);

#endif