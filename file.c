#include "file.h"

/******************************************************************************
 * file_extention()
 *
 * Arguments: file_name - name of the file
 * 			  
 * Returns: sep - extention of the file
 *
 * Description: returns the file extention
 *
*****************************************************************************/
const char *file_extention(const char* file_name){
    const char *sep = strrchr(file_name, '.');
	if (sep == NULL) {
		exit(0);
	}
    if(!sep || sep == file_name){
        return sep+1;
	}
	return sep;
}


/******************************************************************************
 * output_file()
 *
 * Arguments: file_name - name of the file
 * 			  
 * Returns: fp
 *
 * Description: returns the file pointer to the output file
 *
*****************************************************************************/
FILE* output_file(char* file_name) {
	FILE* fp;
	char* name;

	name = (char*)malloc((strlen(file_name) + 2) * sizeof(char));
	strcpy(name, file_name);
	name[strlen(name) - 4] = '\0';
	strcat(name, "paths");
    fp = fopen(name, "w");
	free(name);
	return fp;
}


/******************************************************************************
 * Problem_file()
 *
 * Arguments: main_array - array of arrays with dictionary words, sorted by size
 * 			  counter - array with the sizes of each word array
 * 		      fPtr - pointer to the .pals file
 * 			  fp_out - pointer to the .dict file
 * 			  graphs - array with graphs for each size
 * 			  
 * Returns: void
 *
 * Description: reads .pals file, creates graph and finds solution (path)
 *
*****************************************************************************/
void Problem_file(char** main_array[],int* counter, FILE* fPtr, FILE* fp_out, Graph* graphs[46]) 
{
	int error = -1;
	int i;
	char fst_word[46] = "";
	char sec_word[46] = "";
	int max_changes = 0;
	int n1 = 0;
	int n2 = 0;
	int size;
	int diff = 0;
	//flags: this will indicate whether the array has been 
	//quicksorted and whether the graph has been created
	//for each size
	int flags[46]={ 0 };
	//graph_max: biggest max_changes for each size
	int graph_max[46]={ 0 };

	//reads the file to get the biggest max_changes for each size of the word
    while (fscanf(fPtr, "%s %s %d", fst_word, sec_word, &max_changes) == 3){
		size = strlen(fst_word);
		diff = diff_letters(fst_word,sec_word,size,size);
		if(flags[size] == 0){ // if it hasn't been quicksorted
			quicksort(main_array[size], counter[size]);
			flags[size] = 1;
		}
		n1 = binarySearch(fst_word, main_array[size], 0, counter[size] - 1);
		n2 = binarySearch(sec_word, main_array[size], 0, counter[size] - 1);
		if(max_changes > graph_max[size] && n1 != n2 && diff != 1 &&
		(n1 !=-1 && n2 !=-1))
		{
			if(max_changes > size)
				graph_max[size] = size;
			else
				graph_max[size] = max_changes;
		}
    }
	//reset array of flags
	for(i = 0; i<46;i++)
		flags[i] = 0 ;
	rewind(fPtr);

	//solves the problem- creates a graph and finds paths
	while (fscanf(fPtr, "%s %s %d", fst_word, sec_word, &max_changes) == 3)
	{
		size = strlen(fst_word);
		diff = diff_letters(fst_word,sec_word,size,max_changes);
		if (max_changes < 0) // if the number of changes possible is negative
		{
			fprintf(fp_out, "%s %d\n%s\n\n", fst_word, error,sec_word);
		}
		else if (strlen(fst_word) != strlen(sec_word)) // different lengths
		{
			fprintf(fp_out, "%s %d\n%s\n\n", fst_word, error,sec_word);
		}else if (counter[size] == 0)// if there are no words with that length
		{
			fprintf(fp_out, "%s %d\n%s\n\n", fst_word, error,sec_word);
		} else {
			n1 = binarySearch(fst_word, main_array[size], 0, counter[size] - 1);
			n2 = binarySearch(sec_word, main_array[size], 0, counter[size] - 1);
			if (n1 == -1 || n2 == -1) //if one of the words aren't in the dictionary
			{
				fprintf(fp_out, "%s %d\n%s\n\n", fst_word, error, sec_word);
			} else if (n1==n2){ // if the words are the same
				fprintf(fp_out, "%s 0\n%s\n\n", fst_word, sec_word);
			}else if (diff == 1){ // if there is only one mutation between both words
				fprintf(fp_out, "%s 1\n%s\n\n", fst_word,sec_word);
			}else
			{
			//if graph hadn't been created
			if (flags[size] == 0)
			{
				graphs[size] = fill_graph(counter[size], size, main_array[size], graph_max[size]);
				flags[size] = 1;
			}

			//apply dksitra
			dijkstra(fp_out,graphs[size],main_array[size], n1,n2, max_changes);
			}
		}
	}
	//free graphs
	for(i = 0; i<46; i++){
		if(flags[i]==1){
			free_graph(graphs[i]);
		}
	}
}


/******************************************************************************
 * printPath()
 *
 * Arguments: fp - pointer to output file
 * 			  parent[] - array of previous vertices 
 * 		      j - index of the destination
 * 			  mainArr - array with words of a certain size
 * 			  
 * Returns: void
 *
 * Description: prints path
 *
*****************************************************************************/
void printPath(FILE* fp, int parent[], int j, char** mainArr)
{
    //if j is the source
    if (parent[j]==NO_PREV)
        return;

    printPath(fp, parent, parent[j], mainArr);

    fprintf(fp,"%s\n", mainArr[j]);
}

/******************************************************************************
 * printSolution()
 *
 * Arguments: fp - pointer to output file
 * 			  src - source word
 * 			  parent[] - array of previous vertices 
 * 		      i - index of the destination
 * 			  cost - array of costs, depending on the destination
 * 			  mainArr - array with words of a certain size
 * 			  
 * Returns: void
 *
 * Description: prints solution
 *
*****************************************************************************/
void printSolution(FILE* fp, int src, int i, int* cost, int* parents, int V, char** mainArr){
 	if (cost[i] ==  INT_MAX){
 		fprintf(fp,"%s -1\n%s\n\n", mainArr[src],mainArr[i]);
 	} else{
 		fprintf(fp,"%s %d\n", mainArr[src], cost[i]);
 		printPath(fp, parents,i,mainArr);
 		fprintf(fp,"\n");
 	}
}