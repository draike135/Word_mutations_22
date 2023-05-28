#include "dijkstra.h"

/******************************************************************************
 * dijkstra()
 *
 * Arguments: fp - pointer to the output
 *            graph
 * 			  main_array
 * 			  src - source word
 *            end - end words
 *            max - maximum changes
 * 			  
 * Returns: void
 *
 * Description: find the shortest dijkstra
 *
 *****************************************************************************/
void dijkstra(FILE* fp, Graph* graph, char** main_array, int src,int end, int max)
{
    //V: extract number of vertices from graph
	int V = graph->num_V;

    //cost: int vector that saves the
    //cost from the source to each vertex
	int cost[V];

    //prev: int vector that saves the previous vectors
	int prev[V];

    //initialize prev
	for(int v = 0; v<V; v++)
		prev[v] = NO_PREV;

    //create heap
	Heap* h = createHeap(V);

    //create array of heap nodes
	HeapNode* pointerarray[V];

    //initialize heap nodes
	for (int v = 0; v < V; v++)
	{
		cost[v] = INT_MAX;
		h->array[v] = newHeapNode(v,cost[v]);
		h->pos[v] = v;
		pointerarray[v]= h->array[v];
	}
	free(h->array[src]);
    //create source heap node
	h->array[src] = newHeapNode(src, cost[src]);
	pointerarray[src] = h->array[src];
	h->pos[src] = src;
	cost[src] = 0;
	decreaseKey(h, src, cost[src]);
	h->size = V;

    //while h contains all nodes whose shortest
    //distance hasn't been finalized
	while (!isEmpty(h))
	{
        //extracts the vertex with mininum
        //distance value
		HeapNode* heapNode =extractMinimum(h);

        //stores the extracted vertex index
		int u = heapNode->v;

        //goes through all the adjacent vertices of u
        //and updates the cost
		AdjNode* pCrawl =graph->adj_list[u];
		while (pCrawl != NULL)
		{
			int v = pCrawl->vertex;

            //if we find the target vertex
			if(u == end)
				break;

            //if the distance to the vertex v is not initialized
            //and the cost to v through u is less than the previous one
			if (isInHeap(h, v) && cost[u] != INT_MAX && pCrawl->cost + cost[u] < cost[v] && pCrawl->cost <= max*max )
			{
				cost[v] = cost[u] + pCrawl->cost;
				prev[v]=u;
				// update distance
				decreaseKey(h, v, cost[v]);
			}
			pCrawl = pCrawl->next;
		}
	}
    //print solution
	printSolution(fp, src, end, cost, prev,V, main_array);

    //free heap
	for (int v = 0; v < V; v++)
	{
		free(pointerarray[v]);
	}
	free(h->pos);
	free(h->array);
	free(h);
}