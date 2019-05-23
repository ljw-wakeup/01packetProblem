#include "MergeSort.h"
#include<iostream>
#define MAXNUM 1000000
using namespace std;


long leftArray[MAXNUM];
long rightArray[MAXNUM];

void MergeSort::Merge(long p, long q, long r) {
	long i = 0, j = 0, k = 0;
	for (i = 0; i <= q - p; i++) 
		leftArray[i] = head[p + i];
	for (i = 0; i <= r - q - 1; i++)
		rightArray[i] = head[q + 1 + i];
	i = 0;
	j = 0;
	for (k = p; k <= r; k++) {
		if (i <= q - p && j <= r - q - 1) {
			if (leftArray[i] <= rightArray[j]) {
				head[k] = leftArray[i];
				i++;
			}
			else {
				head[k] = rightArray[j];
				j++;
			}
		}
	}
	if (i <= q - p) {
		while (k++ <= r) 
			head[k] = leftArray[i++];
	}
	
	else if (j <= r - q - 1) {
		while (k++ <= r) 
			head[k] = rightArray[j++];

	}
}
//[p...q],[q+1...r]
void MergeSort::Merge_sort(long p, long r) 
{
	long q;
	if (p < r) {
		q = floor((p + r) / 2);
		Merge_sort(p, q);
		Merge_sort(q + 1, r);
		Merge(p, q, r);
	}
		
}
long* MergeSort::SortConsequence() {
	return head;
}


MergeSort::MergeSort(long* Head, long Length)
{
	head = Head;
	length = Length;
	Merge_sort(0, length - 1);
}


MergeSort::~MergeSort()
{
}
