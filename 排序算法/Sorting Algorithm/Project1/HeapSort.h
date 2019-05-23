#pragma once
using namespace std;


class HeapSort
{
private:
	long* head;
	long length;
	long heapEndIndex;    //���±�Ϊ��������׼[1...length]
	void MaxHeapify(long heapHead);   //���±�Ϊ��������׼[1...length]
	void BuildMaxHeap();
	void Heap_sort();

public:
	HeapSort(long* Head, long Length);
	~HeapSort();
	long* SortConsequence();
};

