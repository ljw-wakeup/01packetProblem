#include<iostream>
#include "HeapSort.h";

//�����������ΪA[],ע���У��±�Ϊ[1...length]
//ʵ�ʴ����У��±�Ϊ[0...length - 1]
using namespace std;

void HeapSort::BuildMaxHeap()
{
	long i;
	heapEndIndex = length;
	for (i = floor(length / 2) ; i >= 1; i--) 
		MaxHeapify(i);
}
//heapHead,left,right, heapEndIndex����[1...length]
void HeapSort::MaxHeapify(long heapHead)
{
	long left = heapHead * 2;
	long right = heapHead * 2 + 1 ;
	long largestIndex = 0;
	long temp;

	if (left <= heapEndIndex && head[heapHead - 1] < head[left - 1])
		largestIndex = left;
	else largestIndex = heapHead;

	if (right <= heapEndIndex && head[right - 1] > head[largestIndex - 1])
		largestIndex = right;

	if (largestIndex != heapHead) {
		temp = head[largestIndex - 1];
		head[largestIndex - 1] = head[heapHead - 1];
		head[heapHead - 1] = temp;
		MaxHeapify(largestIndex);
	}
}

void HeapSort::Heap_sort()
{
	long i = 0;
	long temp = 0;
	BuildMaxHeap();            //���������
	heapEndIndex = length;
	for (i = length - 1; i >= 0; i--) {
		//exchange A[i]��A[1]
		temp = head[0];
		head[0] = head[i];
		head[i] = temp;
		heapEndIndex--;
		MaxHeapify(1);
		
	}
}

long* HeapSort::SortConsequence() {
	return head;
}
HeapSort::HeapSort(long* Head, long Length)
{
	head = Head;
	length = Length;
	heapEndIndex = Length;
	Heap_sort();

}

HeapSort::~HeapSort()
{
}
