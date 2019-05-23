#pragma once
using namespace std;

class MergeSort
{
private:
	long length;
	long* head;
	void Merge_sort(long p,long r);
	void Merge(long p, long q, long r);
public:
	MergeSort(long* Head, long Length);
	~MergeSort();
	long* SortConsequence();
};

