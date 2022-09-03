#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
#include<unordered_map>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

struct node {
	int addr;
	int data;
	int next;
	node() {}
	node(int a, int b, int c) :addr(a), data(b), next(c) {}
};
int head;
int N, K;
unordered_map<int, struct node> dat;
void input() {
	cin >> head >> N >> K;
	for (int i = 0; i < N; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		dat[a] = node(a, b, c);
	}
}

vector<struct node> mylist;
void make_list() {
	struct node n = dat[head];
	while (true) {
		mylist.push_back(n);
		if (n.next == -1)
			break;
		n = dat[n.next];
	}


}

void fillnext() {
	//ÐÞ¸ÄnextÓò
	for (int i = 0; i < mylist.size(); i++) {
		if (i != mylist.size() - 1)
			mylist[i].next = mylist[i + 1].addr;
		else
			mylist[i].next = -1;
	}
}

//
vector<struct node> l1,l2,l3;
void split() {
	for (int i = 0; i < mylist.size(); i++) {
		if (mylist[i].data < 0) {
			l1.push_back(mylist[i]);
		}
		else if (mylist[i].data <= K) {
			l2.push_back(mylist[i]);
		}
		else {
			l3.push_back(mylist[i]);
		}
	}
	mylist.clear();
	mylist.insert(mylist.end(),l1.begin(),l1.end());
	mylist.insert(mylist.end(), l2.begin(), l2.end());
	mylist.insert(mylist.end(), l3.begin(), l3.end());
	fillnext();
}

int main(void) {
	input();
	make_list();
	split();

	for (int i = 0; i < mylist.size(); i++) {
		struct node& n = mylist[i];
		if(i!=mylist.size()-1)
			printf("%05d %d %05d\n", n.addr, n.data, n.next);
		else
			printf("%05d %d %d\n", n.addr, n.data, n.next);
	}
}

/*
00100 9 10
23333 10 27777
00000 0 99999
00100 18 12309
68237 -6 23333
33218 -4 00000
48652 -2 -1
99999 5 68237
27777 11 48652
12309 7 33218

*/