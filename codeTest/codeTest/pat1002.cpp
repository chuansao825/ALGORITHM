#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<stack>
using namespace std;

//key为指数，value为系数
map<int, double> map1;


void insert_into_map(int k,map<int,double>& mymap) {
	int n;
	double a;
	for (int i = 0; i < k; i++) {
		cin >> n >> a;
		if (mymap.find(n) != mymap.end()) {
			mymap[n] += a;
		}
		else
			mymap[n] = a;
	}
}

void input() {
	int k1, k2;
	cin >> k1;
	insert_into_map(k1, map1);
	cin >> k2;
	insert_into_map(k2, map1);
}


struct node {
	int n;
	double a;
	node(int _n, double _a) :n(_n), a(_a) {}
};

int main(void) {
	input();

	
	//处理系数为0的特殊情况，直接删去
	map<int, double> map2;
	for (auto it = map1.begin(); it != map1.end(); it++) {
		if (it->second != 0)
			map2.insert(make_pair(it->first, it->second));
	}
	map1.swap(map2);

	int k = map1.size();

	stack<struct node> mystack;
	for (auto it = map1.begin(); it != map1.end(); it++) {
		int n = it->first;
		double a = it->second;
		mystack.push(node(n, a));
	}

	//output
	printf("%d",k);
	//k为0时后面不能有空格
	if (k != 0)
		printf(" ");
	while (!mystack.empty()) {
		struct node temp = mystack.top();
		printf("%d %.1f", temp.n, temp.a);
		if (mystack.size() > 1) {
			cout << " ";
		}
		mystack.pop();
	}
	cout << endl;

	return 0;
}


/*
2 1 2.4 0 3.2
2 2 1.5 1 0.5

1 3 5.5
1 3 -5.5

*/