#include "heap.h"


/******************************************************************************
 * swapHeapNode()
 *
 * Arguments: HeapNode** a, HeapNode** b - Nodes to be swapped
 * 			  
 * Returns: void
 *
 * Description: swap nodes 
 *
*****************************************************************************/
void swapHeapNode(HeapNode** a, HeapNode** b)
{
	HeapNode* t = *a;
	*a = *b;
	*b = t;
}


/******************************************************************************
 * decreaseKey()
 *
 * Arguments: heap
 * 			  v
 * 			  cost
 * 			  
 * Returns: void
 *
 * Description: Add new path to a certain node at a lower cost
 *
*****************************************************************************/
void decreaseKey(Heap* heap, int v, int cost)
{
	int i = heap->pos[v];
	heap->array[i]->cost = cost;
	while (i && heap->array[i]->cost < heap->array[(i - 1) / 2]->cost)
	{
		heap->pos[heap->array[i]->v] = (i - 1) / 2;
		heap->pos[heap->array[(i - 1) / 2]->v] = i;
		swapHeapNode(&heap->array[i], &heap->array[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}


/******************************************************************************
 * Heapify()
 *
 * Arguments: heap
 * 			  v
 * 			  cost
 * 			  
 * Returns: void
 *
 * Description: create a heap data structure
 *
*****************************************************************************/
void Heapify(Heap* heap, int idx)
{
	int smallest, left, right;
	//subtree root
	smallest = idx;
	//index of the left child
	left = 2 * idx + 1;
	//index of the right child
	right = 2 * idx + 2;

	// if the left child is smaller than the root, the left child is redefined
	// as the smallest
	if (left < heap->size && heap->array[left]->cost < heap->array[smallest]->cost)
		smallest = left;

	// if the right child is smaller than the root, the right child is redefined
	// as the smallest
	if (right < heap->size && heap->array[right]->cost < heap->array[smallest]->cost)
		smallest = right;

	//confirm whether the smallest value is at the root 
	//with the smallest value,if not the root and the
	//smallest value are swapped
	if (smallest != idx){
		HeapNode* smallestNode = heap->array[smallest];
		HeapNode* idxNode = heap->array[idx];

		//swap positions
		heap->pos[smallestNode->v] = idx;
		heap->pos[idxNode->v] = smallest;

		//swap nodes
		swapHeapNode(&heap->array[smallest],
			&heap->array[idx]);

		Heapify(heap, smallest);
	}
}

/******************************************************************************
 * isEmpty()
 *
 * Arguments: heap
 * 			  
 * Returns: heap->size == 0
 *
 * Description: returns 1 if the heap is empty, else returns 0
 *
*****************************************************************************/
int isEmpty(Heap* heap)
{
	return heap->size == 0;
}

/******************************************************************************
 * createHeap()
 *
 * Arguments: maxSize - capacity of the heap
 * 			  
 * Returns: heap
 *
 * Description: creates heap
 *
*****************************************************************************/
Heap* createHeap(int maxSize)
{
	Heap* heap =(Heap*)malloc(sizeof(Heap));
	heap->pos = (int*)malloc(maxSize * sizeof(int));
	heap->size = 0;
	heap->maxSize = maxSize;
	heap->array =(HeapNode**)malloc(maxSize *sizeof(HeapNode*));
	return heap;
}

/******************************************************************************
 * newHeapNode()
 *
 * Arguments: v - destination vertex
 * 			  cost - cost of the src to v
 * 			  
 * Returns: heapNode
 *
 * Description: creates heap node
 *
*****************************************************************************/
HeapNode* newHeapNode(int v, int cost)
{
	HeapNode* heapNode =(HeapNode*)malloc(sizeof(HeapNode));
	heapNode->v = v;
	heapNode->cost = cost;
	return heapNode;
}

/******************************************************************************
 * extractMinimum()
 *
 * Arguments: heap
 * 			  
 * Returns: root
 *
 * Description: removes the minimum element in the heap
 *
*****************************************************************************/
HeapNode* extractMinimum(Heap* heap)
{
	if (isEmpty(heap))
		return NULL;

	//stores the root
	HeapNode* root = heap->array[0];

	//replace root node with last node
	HeapNode* lastNode = heap->array[heap->size - 1];
	heap->array[0] = lastNode;

	//update position of last node
	heap->pos[root->v] = heap->size - 1;
	heap->pos[lastNode->v] = 0;

	//reduce heap size and heapify root
	--heap->size;
	Heapify(heap, 0);

	return root;
}


/******************************************************************************
 * isInHeap()
 *
 * Arguments: heap
 * 			  v - vertex
 * 			  
 * Returns: bool
 *
 * Description: sees if the vertex is in the heap
 *
*****************************************************************************/
bool isInHeap(Heap* heap, int v)
{
	if (heap->pos[v] < heap->size)
		return true;
	return false;
}