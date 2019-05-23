#pragma once
using namespace std;

class QuickSort
{
private:
	long* head;
	long length;
	void Quick_sort(long p, long r);
	long Partition(long p, long r);

public:
	QuickSort(long* Head, long Length);
	~QuickSort();
	long* SortConsequence();
};

