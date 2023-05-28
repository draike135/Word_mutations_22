#ifndef _GRAPH_H_
#define _GRAPH_H_

/*Import System Files*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

/*Import Local Files*/
#include "array.h"


typedef struct Adj_Node AdjNode;
typedef struct path_graph Graph;
/*structs*/
struct Adj_Node
{
	int cost;
	int vertex;
	AdjNode* next;
};

struct path_graph
{
	int num_V;
	AdjNode **adj_list;
};



/*Functions*/
int diff_letters(char* w1, char* w2, int wordLength,int max);
AdjNode* createNode(int V, int cost);
Graph* createGraph(int v);
void free_graphs(Graph* graphs[46]);
void free_graph(Graph *graph);
Graph* fill_graph(int num_of_words, int size_of_words, char** words_dict,int max);

# endif