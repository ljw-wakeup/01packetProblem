#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include "binaryPacket.h"

using namespace std;

void getInt(string& s, int* a, int n)
{
	istringstream iss(s);
	int num, res = 0;
	int i = 1;
	while (i<=n) {
		iss >> num;
		a[i-1] = num;
		i++;
	}
}

int main() 
{
//	int w[8] = { 1,2,6,3,2,5,7,3 };
//	int v[8] = { 2,4,10,5,3,5,6,1 }; 
	int* w;
	int* v;
	int c = 20;
	int n = 8;
	ifstream infile;
	infile.open("input.txt", ios::binary);
	cout << "Reading from the file" << endl;
	// line1
	string data_n;
	getline(infile, data_n);
	cout << data_n << endl;
	n = atoi(data_n.c_str());
	w = (int*)malloc(n * sizeof(int));
	v = (int*)malloc(n * sizeof(int));
	// line2
	string data_c;
	getline(infile, data_c);
	cout << data_c << endl;
	c = atoi(data_c.c_str());
	// line3
	string data_w;
	getline(infile, data_w);
	cout << data_w << endl;
	getInt(data_w, w,n);
	// line4
	string data_v;
	getline(infile, data_v);
	cout << data_v << endl;
	getInt(data_v, v,n);

//
	binaryPacket packet(v, w, c, n);




	packet.Method("DP");
	cout << "��̬�滮" << endl;
	int answer = packet.PrintAnswer();

	ofstream outfile;
	outfile.open("ouput.txt");
	outfile << "��̬�滮" << answer << endl;

//		
	packet.Method("exhaustive");
	cout << "��ٷ�" << endl;
	answer = packet.PrintAnswer();
	outfile << "��ٷ�" << answer << endl;
//
	packet.Method("memorized");
	cout << "����¼��" << endl;
	answer = packet.PrintAnswer();
	outfile << "����¼��" << answer << endl;

// 
	packet.Method("backtrack");
	cout << "���ݷ�" << endl;
	answer = packet.PrintAnswer();
	outfile << "���ݷ�" << answer << endl;
//  

	packet.Method("branch&bound");
	answer = packet.max;
	cout << "��֧�޽編" << answer << endl;
	outfile << "��֧�޽編" << answer << endl;
//
	packet.Method("MC");
	answer = packet.max;
	cout << "���ؿ���" << answer << endl;
	outfile << "���ؿ���" << answer << endl;

}

//"DP""memorized" "exhaustive""backtrack""branch&bound""MC"