#pragma once
#define UP 1
#define DOWN 0
using namespace std;

class InsertSort
{
private:
	bool direction;
	long length;
	long* head;
	void Insert_sort();

public:
	InsertSort(long* Head, long Length, bool direction);
	~InsertSort();
	long* SortConsequence();
};

