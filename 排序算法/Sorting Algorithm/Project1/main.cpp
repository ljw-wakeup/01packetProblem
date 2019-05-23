#include<iostream>
#include "HeapSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "InsertSort.h"
#include "Windows.h"
#include "time.h"
#define TEST
#define WINDOWS_IMPL
long randomList[1000000] = { 0 };
long randomList1[1000000] = { 0 };
long numlist[7] = { 1000, 10000, 50000, 100000, 200000, 500000, 1000000 };
using namespace std;


void renew() {
	for (long i = 0; i < 1000000; i++) {
		randomList1[i] = randomList[i];
	}
}

int main(void)
{
	long* consequence = NULL;
	long i;
	int k;
#ifdef TEST
	long testlist[7] = { 4, 12, 8, 6, 11, 5, 9 };
	HeapSort heapSortTest(testlist, 7);
	consequence = heapSortTest.SortConsequence();
	for (i = 0; i < 7; i++) {
		cout << consequence[i] << '\t';

	}
	cout << endl;
#endif
#ifdef NOTEST
	for (k = 0; k < 10; k++){
		cout << "experiment:" << k + 1 << endl;
		srand((unsigned)time(NULL));
		for (i = 0; i < 1000000; i++) {
			randomList[i] = rand() % 100000;
			//cout << randomList[i] << '\t';
		}
		//cout << endl;
		for (i = 6; i <= 6; i++) {
			cout << "scale is" << numlist[i] << endl;
			DWORD start_time1 = GetTickCount64();
			QuickSort quickSort(randomList1, numlist[i]);
			renew();
			DWORD end_time1 = GetTickCount64();
			cout << "Time of quick_sort is" << end_time1 - start_time1 << "ms." << endl;
			cout << "scale is" << numlist[i] << endl;
			DWORD  start_time = GetTickCount64();
			InsertSort insertSort(randomList1, numlist[i]);
			renew();
			DWORD end_time = GetTickCount64();
			cout << "Time of insert_sort is" << end_time - start_time << "ms." << endl;
			cout << "scale is" << numlist[i] << endl;
			start_time = GetTickCount64();
			HeapSort heapSort(randomList1, numlist[i]);
			renew();
			end_time = GetTickCount64();
			cout << "Time of heap_sort is" << end_time - start_time << "ms." << endl;
			cout << "scale is" << numlist[i] << endl;
			start_time = GetTickCount64();
			MergeSort mergeSort(randomList1, numlist[i]);
			renew();
			end_time = GetTickCount64();
			cout << "Time of merge_sort is" << end_time - start_time << "ms." << endl;
		}
	}
#endif
	
}


	/*
	consequence = insertSort.SortConsequence();
	for (i = 0; i < MAXNUM; i++) {
		cout << consequence[i] << '\t';
	}
	cout << endl;


	
	consequence = heapSort.SortConsequence();
	for (i = 0; i < MAXNUM; i++) {
		cout << consequence[i] << '\t';
	}
	cout << endl;
	/*QuickSort quickSort(randomList, length);
	consequence = quickSort.SortConsequence();
	for (i = 0; i < MAXNUM; i++) {
		//cout << consequence[i] << '\t';
	}
	cout << endl;

	MergeSort mergeSort(randomList, length);
	consequence = mergeSort.SortConsequence();
	for (i = 0; i < MAXNUM; i++) {
		cout << consequence[i] << '\t';
	}
	cout << endl;
	*/

