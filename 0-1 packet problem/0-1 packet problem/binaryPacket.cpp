#include "binaryPacket.h"
#include<iostream>
#include<math.h>

void binaryPacket::PrintAnswer()
{
	for (int i = 0; i < n; i++) {
		cout << x[i] << '\t';
	}
	cout << endl;
}
void binaryPacket::PrintMij() {
	for (int i = 0; i <= n - 1; i++) {
		for (int j = 0; j <= c; j++)
			cout << m[i][j] << '\t';
		cout << endl;
	}
}
binaryPacket::binaryPacket(int v[], int w[], int c, int n, string method)
{
	this->v = v;
	this->w = w;
	this->c = c;
	this->n = n;
	this->m =(int**) malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) m[i] = (int*)malloc((c + 1) * sizeof(int));
	for (int i = 0; i <= n - 1; i++)
		for (int j = 0; j <= c; j++)
			m[i][j] = 0;
	this->x = (int*)malloc(n * sizeof(int));
	for (int i = 0; i <= n - 1; i++) x[i] = 0;
	if (method == "DP") DP_packet();
	else if (method == "exhaustive") Exh_packet();
	else if (method == "memorized") Mem_Packet();
	else if (method == "backtrack") BackTrack_Packet();
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

//00000 00001 00010  00011 00100 00101 00110 00111 ... 11111 = 100000-1
void binaryPacket::Exh_packet()
{
	int max = 0;
	int* temp = (int*)malloc(n * sizeof(int));
	for (int i = 0; i <= (int)pow(2, n) - 1; i++) {
		int k = i;
		int sum = 0;
		for (int j = 0 ; j < n; j++) {
			temp[j] = 1 & (k >> j);
			sum += temp[j] * v[j];
		}
		if (sum > max && sum <= c) {
			max = sum;
			for (int j = 0; j < n; x[j] = temp[j++]);
		}
	}
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
		if (w[i] <= c) {
			m[i][j] = (Mem_Lookup(i + 1, j) > Mem_Lookup(i + 1, j - w[i]) + v[i]) ? Mem_Lookup(i + 1, j) : Mem_Lookup(i + 1, j - w[i]) + v[i];
		}
		else m[i][j] = Mem_Lookup(i + 1, j);
	}
	return m[i][j];
}

void binaryPacket::BackTrack_Packet()
{
	int* temp = (int*)malloc(n * sizeof(int));
	cout << BT_knap(0, 0, 0, 0, temp) << endl;
	
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



binaryPacket::~binaryPacket()
{
}
