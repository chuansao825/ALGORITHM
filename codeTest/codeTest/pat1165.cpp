#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

struct mynode {
	int addr;
	int data;
	int next;
	mynode(int a,int b,int c):addr(a),data(b),next(c){}
	mynode(){}
};
int first;
int N, K;
//key为addr，value为mynode
unordered_map<int, struct mynode> map1;
void input() {
	cin >> first >> N >> K;
	for (int i = 0; i < N; i++) {
		int addr, data, next;
		cin >> addr >> data >> next;
		map1.insert(make_pair(addr, mynode(addr, data, next)));
	}
}

vector<mynode> mylist;
void makelist() {
	struct mynode n = map1[first];	
	while (true) {
		mylist.push_back(n);
		if (n.next == -1)
			break;
		n = map1[n.next];
	}
}

int main(void) {
	input();
	makelist();

	//输出
	//为了避免脏数据，即给的node不在链表上的情况
	N = mylist.size();
	int groupnum = N % K == 0 ? N / K : N / K + 1;
	stack<mynode> s;
	for (int i = 0; i < groupnum; i++) {
		int lb = K * i;
		int ub = K * (i + 1) - 1 > N-1 ? N-1 : K * (i + 1) - 1;
		for (int j = ub; j >= lb; j--) {
			s.push(mylist[j]);
		}
	}
	//修改前后指针
	vector<mynode> newlist;
	while (!s.empty()) {
		struct mynode n = s.top();
		s.pop();
		newlist.push_back(n);
	}
	for (int i = 0; i < newlist.size()-1; i++) {
		newlist[i].next = newlist[i + 1].addr;
	}
	newlist[newlist.size() - 1].next = -1;

	for(int i = 0; i < newlist.size();i++) {
		struct mynode n = newlist[i];
		if(n.next==-1)
			printf("%05d %d %d\n", n.addr, n.data, n.next);
		else
			printf("%05d %d %05d\n", n.addr, n.data, n.next);
	}
	return 0;
}



/*
00100 8 3
71120 7 88666
00000 4 99999
00100 1 12309
68237 6 71120
33218 3 00000
99999 5 68237
88666 8 -1
12309 2 33218

00100 8 1
71120 7 88666
00000 4 99999
00100 1 12309
68237 6 71120
33218 3 00000
99999 5 68237
88666 8 -1
12309 2 33218

00000 1 1
00000 10 -1

00100 8 4
71120 7 88666
00000 4 99999
00100 1 12309
68237 6 71120
33218 3 00000
99999 5 68237
88666 8 -1
12309 2 33218


00100 8 5
71120 7 88666
00000 4 99999
00100 1 12309
68237 6 71120
33218 3 00000
99999 5 68237
88666 8 -1
12309 2 33218

00000 2 1
00001 2 -1
00000 1 00001

00100 9 3
71120 7 88666
00000 4 99999
00100 1 12309
68237 6 71120
33218 3 00000
99999 5 68237
88666 8 -1
12309 2 33218
12345 9 81932

*/