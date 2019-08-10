/* 
 * Filename: quickSort.cpp
 * Usage: ./quickSort QuickSort.txt
 * Description: The command line program quickSort.cpp first
 *		reads the file QuickSort.txt, which contains
 *		the integers 1 through 10000 inclusive in 
 *		some unsorted order. The program outputs the
 *		number of comparisons made depending on the
 *		choice of pivot. 
 */

#include <iostream>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>

// argv index of input file
#define IN_IDX 1 

// expected number of arguments
#define EXPECTED_ARGS 2

// size of array
#define ARRAY_SIZE 10000

// Option 1: pivot always first element
#define PIV_FIRST 1

// Option 2: pivot always last element
#define PIV_LAST 2

// Option 3: pivot is median of first, last, middle
#define PIV_MED 3

using namespace std;

// swaps the pivot with the first element in the array
void choosePivot(unsigned int A[], unsigned int l, 
		 unsigned int r, unsigned int pivOpt)
{
	// used for swapping
	unsigned int temp;

	// pivot is last element of array
	if( pivOpt == PIV_LAST ){
		temp = A[l];
		A[l] = A[r];
		A[r] = temp;
	}

	// pivot is median of first, last, middle elements
	if( pivOpt == PIV_MED) {
		vector < pair <unsigned int, int> > comp;
		comp.push_back(make_pair(A[l],l));
		comp.push_back(make_pair(A[r],r));
		comp.push_back(make_pair(A[(l+r)/2],(l+r)/2));
		sort(comp.begin(), comp.end());
		int pivot = comp[1].second;
		temp = A[pivot];
		A[pivot] = A[l];
		A[l] = temp;
	}	
}

/* partitions the array so that everything to the left
 * of the pivot is less than the pivot and everything
 * to the right of the pivot is greater than the pivot
 */
int partition( unsigned int A[], int l, int r)
{
	/* keeps track of which elements are less than
	 * the pivot and which are greater. More exactly,
	 * A[l+1],...,A[i-1] are less than the pivot while
	 * A[i+1],...,A[j-1] are greater than the pivot.
	 */
	int i = l+1;

	/* keeps track of which elements have been examined.
	 * More exactly, A[j],...,A[n] are not yet examined.
	 */
	int j = l+1;

	// used for swapping
	unsigned int temp;

	// do a linear scan through the array
	for(j = l+1; j <= r; ++j) {

		/* if A[j] is smaller than the pivot,
		 * swap it with A[i], the first element
		 * that is bigger than the pivot.
		 * Increment i.
		 */
		if( A[j] < A[l] ){
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
			i += 1;
		}
	}

	// put the pivot in its rightful position
	temp = A[l];
	A[l] = A[i-1];
	A[i-1] = temp;

	// return i so we can split the array in two
	return i;
} 

/* If the array has length greater than one, choose
 * a pivot, partition the array around the pivot,
 * rinse and repeat on the left and right parts of
 * the array. For an array of size m, quickSort makes
 * m-1 comparisons. Return the total number of 
 * comparisons made.
 */ 
unsigned int quickSort(unsigned int A[], int l, int r, 
		unsigned int pivOpt)
{
	unsigned int compNum = max(r-l,0);
	if( r-l > 0 ){
		//cout << "l : " << l << " r: " << r << " compNum: " 
		//     << compNum << endl;
		choosePivot(A, l, r, pivOpt);
		unsigned int i = partition(A,l,r);
		compNum += quickSort(A, l, i-2, pivOpt);
		compNum += quickSort(A, i, r, pivOpt);
	}
	return compNum;
}

// read input file and return number of comparisons made by quickSort
unsigned int numCompare(const char* inFile, unsigned int pivotOption)
{

	// Allocate an array with ARRAY_SIZE entries
	unsigned int* arr = (unsigned int*) 
        	malloc(ARRAY_SIZE * sizeof(unsigned int));

	bool more_input = true; 
	unsigned int i;
	unsigned int numComparisons = 0;

	// open input file 
    	FILE *in = fopen(inFile, "r"); 
 
	// read the integers in the input file into the array
    	while (more_input) 
    	{ 
        	// write n elements into arr from input file 
        	for (i = 0; i < ARRAY_SIZE; ++i) 
        	{ 
            		if (fscanf(in, "%d\n", &arr[i]) != 1) 
            		{ 
                		more_input = false; 
                		break; 
            		} 
        	}
	}
	
	// close input file
	fclose(in);

	numComparisons = quickSort(arr, 0, ARRAY_SIZE-1, pivotOption);

	// no memory leaks here
        delete[] arr;

	return numComparisons;
	
} 

// Main Driver
int main(int argc, char** argv) 
{

	//Check for Arguments
	if (argc != EXPECTED_ARGS){
		cout << "This program requires 2 arguments!" << endl;
		return -1;
	}

	/* count the number of inversions under the first option
         * when the pivot is always the first number in the array
	 */
	unsigned int compNum1 = 
		numCompare(argv[IN_IDX], PIV_FIRST);

	cout << "The number of comparisons when the first element " 
		<< "is always the pivot is: " << 
                compNum1 << endl;

	unsigned int compNum2 = numCompare(argv[IN_IDX], PIV_LAST);

	cout << "The number of comparisons when the last element "
		<< "is always the pivot is: " <<
		compNum2 << endl;

	unsigned int compNum3 = numCompare(argv[IN_IDX], PIV_MED);
	
	cout << "The number of comparisons when the pivot is always "
		<< "the median of the first, last, and middle elements is: "
		<< compNum3 << endl;
	
} 

