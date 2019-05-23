#pragma once
using namespace std;

class InsertSort
{
private:
	long length;
	long* head;
	void Insert_sort();

public:
	InsertSort(long* Head, long Length);
	~InsertSort();
	long* SortConsequence();
};

