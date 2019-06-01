#pragma once
#include <string>
using namespace std;
typedef struct PriorNode {
	//注：重载>号会编译出错，因为标准库默认使用元素类型的<操作符来确定它们之间的优先级关系。
	bool operator <(const struct PriorNode& d)const {
		if (up < d.up)
		{
			return true;
		}
		return false;
	}
	int up;
	int cv;
	int cw;
	bool node;
	int number;
}PriorNode;

class binaryPacket
{
private:

	int** m;    //the matrix m[i][j] is the best value of the packet with contain j and the stuff i,i+1,...,n, 
	            //only used in the DP and Memoried
	int* v;    //the value of each stuff
	int* w;   //the weight of each stuff
	int c;    // the contain of the packet
	int n;    //the number of stuffs
	int* x; // answer;
	
	//DP
	void DP_packet();
	void DP_knapsack();
	void DP_traceback();
	//Exhaustive
	void Exh_packet();
	int SimpleBT_knap(int i, int cw, int cv, int bestv, int* temp);
	//Memorized
	void Mem_Packet();
	int Mem_Lookup(int i, int j);
	//backtrack
	void BackTrack_Packet();
	int BT_knap(int i, int cw, int cv, int bestv, int* temp);//i is number of the i-st thing in bag
	//Branch and bound
	int BranchBound();
	int Bound(int i, int cw, int cp);
	// Monte Carlo
	void MC_Packet();
	


public:
	binaryPacket(int v[], int w[], int c, int n);
	void Method(string method);
	~binaryPacket();
	int PrintAnswer();
	void PrintMij();
	int max;
};

