#include "array.h"

/******************************************************************************
 * Array()
 *
 * Arguments: fp_dict - pointer to the dictionary file
 *            main_array - stores dictionary words, sorted by size
 * 			  
 * Returns: main_array
 *
 * Description: Reads a .dict file and sorts the words by their
 * size in a array of arrays
 *
 *****************************************************************************/

char*** array(FILE* fp_dict,char*** main_array,int* counter)
{

	//counter_2: counter to make the array
	int counter_2[46];

	int length;
	char buffer[48];
	int i;

	//initialize arrays
	for (i = 0; i < 46; i++)
	{
		counter[i] = 0;
		main_array[i] = NULL;
		counter_2[i] = 0;
	}
	
	//runs through the dictionary and counts the words of each size
	while ((fscanf(fp_dict, "%s", buffer)) == 1){
		length = strlen(buffer);
		counter[length]++;
	}

	//pointer returns to the beginning
	rewind(fp_dict);

	//if there are words of a certain size, it creates a 2D array for each size
	for (i = 0; i < 46; i++)
	{
		if (counter[i] != 0)
		{
			main_array[i] = Main_list(counter[i], i);
		}
	}

	//runs through the dictionary and fills the 2D array with words
	while ((fscanf(fp_dict, "%s", buffer)) == 1)
	{
		length = strlen(buffer);
		strcpy(main_array[length][counter_2[length]], buffer);
		counter_2[length]++;
	}
	return main_array;
}

/******************************************************************************
 * swap()
 *
 * Arguments: a, b - words to be swapped
 * 			  
 * Returns: void
 *
 * Description: Swaps two words
 *
 *****************************************************************************/
void swap(char** a,char** b) {
	char* temp = *a;
	*a = *b;
	*b = temp;
}

/******************************************************************************
 * quicksort()
 *
 * Arguments: arr - array of a certain size
 *            length - self explanatory 
 * 			  
 * Returns: void
 *
 * Description: sort alphabetically words of the same size
 *
 *****************************************************************************/
void quicksort(char * arr[], int length) {
	int i, piv = 0;
	if (length <= 1)
		return;

	for (i = 0; i < length; i++) {
		// if current arra[] word < pivot word, swaps both words
		if (strcmp(arr[i], arr[length - 1]) < 0)    //the last word is used as a pivot 
			swap(arr + i, arr + piv++);
	}
	//move pivot to the middle
	swap(arr + piv, arr + length - 1);

	//recursively sort 
	quicksort(arr, piv++);
	quicksort(arr + piv, length - piv);
}

/******************************************************************************
 * binarySearch()
 *
 * Arguments: input - word to be found
 *            arr - array of words of a certain sizes
 * 			  l - left subarray
 * 			  r - right subarray
 * 			  
 * Returns: void
 *
 * Description: find a word
 *
 *****************************************************************************/
int binarySearch(char* input, char* arr[], int l, int r)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		//if the word is in the middle, that word
		//is returned
		if (strcmp(arr[mid], input) == 0)
			return mid;

		//if the word is smaller than the middle one, then
		//it must be present in the left subarray
		if (strcmp(arr[mid], input) > 0)
			return binarySearch(input,arr, l, mid - 1);

		//if not, it must be present in the right subarray
		return binarySearch(input,arr, mid + 1, r);
	}

	//if the word doesn't exist
	return -1;
}

/******************************************************************************
 * free_array()
 *
 * Arguments: arr - array of words of a certain sizes
 * 			  n - size of arr
 * 			  
 * Returns: void
 *
 * Description: free array of each size
 *
 *****************************************************************************/
void free_array(char* arr[],int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		free(arr[i]);
	}
	free(arr);
}


/******************************************************************************
 * free_array()
 *
 * Arguments: main - array of arrays of dictionary words
 * 			  counter - size of each array
 * 			  
 * Returns: void
 *
 * Description: free all arrays
 *
*****************************************************************************/
void free_all(char** main[], int* counter)
{
	int i;
	for ( i = 0; i < 47; i++)
	{
		if (counter[i] != 0)
		{
			free_array(main[i], counter[i]);
		}
	}
}

/******************************************************************************
 * Main_list()
 *
 * Arguments: words - number of words
 * 			  size_words - size of words
 * 			  
 * Returns: arr
 *
 * Description: allocate a array of words of a certain size
 *
*****************************************************************************/
char** Main_list(int words, int size_words)
{
	char** arr = (char**)malloc(words * sizeof(char*));
	int i;
	for (i = 0; i < words; i++)
	{
		arr[i] = (char*)malloc(size_words * sizeof(char) + 1);
	}
	return arr;

}