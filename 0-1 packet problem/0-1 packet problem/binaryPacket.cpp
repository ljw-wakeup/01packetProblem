#include "binaryPacket.h"
#include "queue"
#include<iostream>
#include <stdlib.h>
#include<math.h>
#include <time.h> 
#define KK 100000
using namespace std;

int binaryPacket::PrintAnswer()
{
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += x[i] * v[i];
	}
	cout << sum << endl;
	max = sum;
	return sum;
}
void binaryPacket::PrintMij() {
	for (int i = 0; i <= n - 1; i++) {
		for (int j = 0; j <= c; j++)
			cout << m[i][j] << '\t';
		cout << endl;
	}
}
binaryPacket::binaryPacket(int v[], int w[], int c, int n)
{
	this->v = v;
	this->w = w;
	this->c = c;
	this->n = n;
	this->m = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) m[i] = (int*)malloc((c + 1) * sizeof(int));
	for (int i = 0; i <= n - 1; i++)
		for (int j = 0; j <= c; j++)
			m[i][j] = 0;
	this->x = (int*)malloc(n * sizeof(int));
	for (int i = 0; i <= n - 1; i++) x[i] = 0;
}
void binaryPacket::Method(string method){
	if (method == "DP") DP_packet();
	else if (method == "exhaustive") Exh_packet();
	else if (method == "memorized") Mem_Packet();
	else if (method == "backtrack") BackTrack_Packet();
	else if (method == "branch&bound") BranchBound();
	else if (method == "MC")MC_Packet();
}
void binaryPacket::DP_packet()
{
	DP_knapsack();
	DP_traceback();
	
}
void binaryPacket::DP_traceback() 
{
	int c1 = c;
	for (int i = 0; i <= n-2; i++) {
		if (m[i][c1] == m[i + 1][c1]) x[i] = 0;
		else {
			x[i] = 1;
			c1 = c1 - w[i];
		}
	}
	x[n - 1] = (m[n - 1][c1] ? 1 : 0);
}

void binaryPacket::DP_knapsack()
{
	int jMax = 0;
	if (w[n-1] - 1 < c) {
		jMax = w[n-1] - 1;
		for (int j = 0; j <= jMax; j++) m[n-1][j] = 0;
		for (int j = w[n-1]; j <= c; j++) m[n-1][j] = v[n-1];
	}
	else {
		jMax = c;
		for (int j = 0; j <= jMax; j++) m[n-1][j] = 0;
	}
	for (int i = n - 2; i >= 1; i--) {
		if (w[i] - 1 < c) {
			jMax = w[i] - 1;
			for (int j = 0; j <= jMax; j++) m[i][j] = m[i + 1][j];
			for (int j = w[i]; j <= c; j++) m[i][j] = (m[i + 1][j] > m[i + 1][j - w[i]] + v[i]) ? m[i + 1][j] : m[i + 1][j - w[i]] + v[i];
		}
		else {
			jMax = c;
			for (int j = 0; j <= jMax; j++) m[i][j] = 0;
		}
	}
	if (c > w[0] - 1) m[0][c] = m[1][c] > m[1][c - w[0]] + v[0] ? m[1][c] : m[1][c - w[0]] + v[0];
	else m[0][c] = m[1][c];
}


void binaryPacket::Exh_packet()
{
	int* temp = (int*)malloc(n * sizeof(int));
	SimpleBT_knap(0, 0, 0, 0, temp);

}
int binaryPacket::SimpleBT_knap(int i, int cw, int cv, int bestv, int* temp)
{
	if (i > n - 1) {
		if (bestv < cv) {
			bestv = cv;
			for (int j = 0; j < n; x[j] = temp[j++]);
		}
		return bestv;
	}
	else {
		if (cw + w[i] <= c) {
			temp[i] = 1;
			cw = cw + w[i];
			cv = cv + v[i];
			bestv = BT_knap(i + 1, cw, cv, bestv, temp);
			cw = cw - w[i];
			cv = cv - v[i];
		}
		temp[i] = 0;
		bestv = BT_knap(i + 1, cw, cv, bestv, temp);
		
	}
	return bestv;
}

void binaryPacket::Mem_Packet()
{
	//initialized 
	for (int i = 0; i <= n - 1; i++)
		for (int j = 0; j <= c; j++)
			m[i][j] = -1;
	// look up the value of the m[0][c]
	Mem_Lookup(0, c);
	DP_traceback();
}

int binaryPacket::Mem_Lookup(int i, int j)
{
	// look up the m[i][j] and return the m[i][j]
	
	if (m[i][j] != -1) return m[i][j];
	else if (i == n - 1) {
		int jMax;
		if (w[i] - 1 < c) {
			jMax = w[i] - 1;
			for (int j = 0; j <= jMax; j++) m[i][j] = 0;
			for (int j = w[i]; j <= c; j++) m[i][j] = v[i];
		}
		else {
			jMax = c;
			for (int j = 0; j <= jMax; j++) m[i][j] = 0;
		}
	}
	else {
		if (w[i] <= j) {
			m[i][j] = (Mem_Lookup(i + 1, j) > Mem_Lookup(i + 1, j - w[i]) + v[i]) ? Mem_Lookup(i + 1, j) : Mem_Lookup(i + 1, j - w[i]) + v[i];
		}
		else m[i][j] = Mem_Lookup(i + 1, j);
	}
	return m[i][j];
}

void binaryPacket::BackTrack_Packet()
{
	int* temp = (int*)malloc(n * sizeof(int));
	BT_knap(0, 0, 0, 0, temp);
	
}

int binaryPacket::BT_knap(int i, int cw,int cv, int bestv, int* temp)
{
	if (i > n-1) {
		if (bestv < cv) {
			bestv = cv;
			for (int j = 0; j < n; x[j] = temp[j++]);
		}
		return bestv;
	}
	else {
		if (cw + w[i] <= c) {
			int sum = 0;
			for (int t = i; t <= n - 1; sum += v[t++]);
			if (cv + sum > bestv) {
				temp[i] = 1;
				cw = cw + w[i];
				cv = cv + v[i];
				bestv = BT_knap(i + 1, cw, cv, bestv, temp);
				cw = cw - w[i];
				cv = cv - v[i];
			}
		}
		int sum = 0;
		for (int t = i + 1; t <= n - 1; sum += v[t++]);
		if (cv + sum > bestv) {
			temp[i] = 0;
			bestv = BT_knap(i + 1, cw, cv, bestv, temp);
		}
	}
	return bestv;
}

int binaryPacket::BranchBound()
{
	int temp;
	int tempv;
	int tempw;
	int j;
	int* kn = (int*)malloc( n * sizeof(int));
	for (int i = 0; i < n; i++) kn[i] = v[i] / w[i];
	for (int i = 1; i <= n - 1; i++) {
		if (kn[i] <= kn[i - 1])
			continue;
		else {
			temp = kn[i];
			tempw = w[i];
			tempv = v[i];
			for (j = i - 1; j >= 0; j--) {
				if (kn[j] < temp) {
					kn[j + 1] = kn[j];
					w[j + 1] = w[j];
					v[j + 1] = v[j];
				}
				else break;
			}
			kn[j + 1] = temp;
			w[j + 1] = tempw;
			v[j + 1] = tempv;
		}
	}
	//cw为当前装包重量，
	//cv为当前装包价值,
	//bestv为当前最优值

	int cw = 0;
	int cv = 0;
	int bestv = 0;
	int i = 1;
	int up = 0; //up为结点的价值上界；
	priority_queue<PriorNode> q;       //定义优先队列
	up = Bound(i,cw,cv); // i是第i个stuff
	while (i != n + 1) {
		// 左孩子即为将i装入背包，右孩子为不将i装入背包
		if (cw + w[i - 1] <= c) {         //左孩子是可行结点，则加入背包
			if (cv + v[i - 1] > bestv) bestv = cv + v[i - 1];
			PriorNode plnode = { up,cv + v[i - 1], cw + w[i - 1], true, i + 1 };
			q.push(plnode);
		}
		up = Bound(i + 1, cw, cv);
		if (up >= bestv) {//如果右子树可能包含最优解
			PriorNode prnode = { up,cv , cw , false, i + 1 };
			q.push(prnode);
		}
		up = q.top().up;
		cv = q.top().cv;
		cw = q.top().cw;
		i = q.top().number;
		q.pop();

	}
	max = cv;
	return cv;
}
int binaryPacket::Bound(int i, int cw, int cv) {
	int cleft = c - cw;
	int bound = cv;
	while (i <= n && w[i - 1] <= cleft) {
		cleft -= w[i - 1];
		bound += v[i - 1];
		i++;
	}
	//此时i物品还没装但是已经不能完全装下了，所以就按比例把剩下的装下
	if (i <= n) bound += v[i - 1] / w[i - 1] * cleft;
	return bound;
}

void binaryPacket::MC_Packet()
{
	int test[KK] = { 0 };
	srand((unsigned)time(NULL));
	int max = 0;
	for (int j = 0; j <= KK - 1; j++) {
		for (int i = 0; i < n; i++) {
			x[i] = rand() % 2;
			test[j] += x[i] * v[i];
		}
		if (test[j] > c) test[j] = -1;
		if (test[j] > max) max = test[j];
	}
	this->max = max;
}



binaryPacket::~binaryPacket()
{
}
