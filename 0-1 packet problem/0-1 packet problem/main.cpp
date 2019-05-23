#include<iostream>
#include "binaryPacket.h"
using namespace std;
int main() 
{
	int w[3] = { 2,3,4 };
	int v[3] = { 2,3,4 };
	int c = 6;
	int n = 3;
	binaryPacket packet(v, w, c, n, "backtrack");
	packet.PrintAnswer();
	
}
//"memorized" "exhaustive"