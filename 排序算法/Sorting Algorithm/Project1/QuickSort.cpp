#include<iostream>
#include "QuickSort.h"
using namespace std;
void QuickSort::Quick_sort(long p, long r)
{
	long q;
	if (p >= r)
		return;
	q = Partition(p, r);
	Quick_sort(p, q - 1);
	Quick_sort(q + 1, r);
}
//i:分区1（小于参考元素的分区）的最后一个元素。j:分区3的第一个元素(分区3：还没有和参考元素比较的分区)
long QuickSort::Partition(long p, long r) 
{
	long i = p-1;
	long j = p;
	long reference = head[r];
	for (j = p; j <= r - 1; j++) {
		if (head[j] < reference) {
			swap(head[i + 1], head[j]);
			i++;
		}
	}
	swap(head[i + 1], head[r]);
	return i + 1;
}

long* QuickSort::SortConsequence() {
	return head;
}

QuickSort::QuickSort(long* Head, long Length)
{
	
	head = Head;
	length = Length;
	Quick_sort(0, length - 1);
}


QuickSort::~QuickSort()
{
}
