#pragma once
#include <string>
using namespace std;
class binaryPacket
{
private:

	int** m;
	int* v;
	int* w;
	int c;
	int n;
	int* x; // answer;
	//DP
	void DP_packet();
	void DP_knapsack();
	void DP_traceback();
	//Exhaustive
	void Exh_packet();
	//Memorized
	void Mem_Packet();
	int Mem_Lookup(int i, int j);
	//backtrack
	void BackTrack_Packet();
	int BT_knap(int i, int cw, int cv, int bestv, int* temp);//i is number of the i-st thing in bag

public:
	binaryPacket(int v[], int w[], int c, int n, string method = "DP");
	~binaryPacket();
	void PrintAnswer();
	void PrintMij();
};

