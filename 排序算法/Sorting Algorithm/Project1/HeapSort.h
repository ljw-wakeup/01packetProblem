#pragma once
using namespace std;


class HeapSort
{
private:
	long* head;
	long length;
	long heapEndIndex;    //该下标为二叉树标准[1...length]
	void MaxHeapify(long heapHead);   //该下标为二叉树标准[1...length]
	void BuildMaxHeap();
	void Heap_sort();

public:
	HeapSort(long* Head, long Length);
	~HeapSort();
	long* SortConsequence();
};

