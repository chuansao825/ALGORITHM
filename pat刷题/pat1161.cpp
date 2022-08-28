#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

struct node {
	int addr;
	int data;
	int next;
	node(int a,int b,int c):addr(a),data(b),next(c){}
	node(){}
};
int head1, head2, N;
map<int,struct node> nodes;
void input() {
	cin >> head1 >> head2 >> N;
	for (int i = 0; i < N; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		nodes.insert(make_pair(a, node(a, b, c)));
	}
}

vector<node> make_list(int head,map<int,struct node> m) {
	struct node n = m[head];
	vector<struct node> v;
	while (true) {
		v.push_back(n);
		if (n.next == -1)
			break;
		else {
			n = m[n.next];
		}
	}
	return v;
}

int main(void) {
	input();
	//还原链表
	vector<struct node> list1 = make_list(head1, nodes);
	vector<struct node> list2 = make_list(head2, nodes);
	//令list1是数量多的
	if (list1.size() < list2.size())
		list1.swap(list2);

	//变形
	reverse(list2.begin(), list2.end());
	vector<struct node> list3;
	int j = 0;	//list2的指针
	for (int i = 0; i < list1.size(); i++) {
		list3.push_back(list1[i]);
		if (i % 2 == 1 && j<list2.size()) {
			list3.push_back(list2[j++]);
		}
	}
	//修改next指针
	for (int i = 0; i < list3.size()-1; i++) {
		list3[i].next = list3[i + 1].addr;
	}
	list3[list3.size() - 1].next = -1;
	//输出
	for (int i = 0; i < list3.size(); i++) {
		struct node n = list3[i];
		if (n.next != -1)
			printf("%05d %d %05d\n", n.addr, n.data, n.next);
		else
			printf("%05d %d %d\n", n.addr, n.data, n.next);
	}
}

/*
00100 01000 7
02233 2 34891
00100 6 00001
34891 3 10086
01000 1 02233
00033 5 -1
10086 4 00033
00001 7 -1

*/