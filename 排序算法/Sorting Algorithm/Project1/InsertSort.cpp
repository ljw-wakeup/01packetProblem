#include "InsertSort.h"
#include<iostream>

using namespace std;

void InsertSort::Insert_sort() {
	long i,j;
	long temp;
	if (direction == UP) {
		for (i = 1; i <= length - 1; i++) {
			if (head[i] >= head[i - 1])
				continue;
			else {
				temp = head[i];
				for (j = i - 1; j >= 0; j--) {
					if (head[j] > temp)
						head[j + 1] = head[j];
					else break;
				}
				head[j + 1] = temp;
			}
		}
	}
	else {
		for (i = 1; i <= length - 1; i++) {
			if (head[i] <= head[i - 1])
				continue;
			else {
				temp = head[i];
				for (j = i - 1; j >= 0; j--) {
					if (head[j] < temp)
						head[j + 1] = head[j];
					else break;
				}
				head[j + 1] = temp;
			}
		}
	}
	

}
long* InsertSort::SortConsequence() {
	return head;
}
InsertSort::InsertSort(long* Head, long Length, bool Direction)
{
	head = Head;
	length = Length;
	direction = Direction;
	Insert_sort();
}


InsertSort::~InsertSort()
{
}
