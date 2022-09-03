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

const int MAX = 10005;
int pr[MAX] = { 0 };
//初始化并查集
void init() {
	for (int i = 0; i < MAX; i++)
		pr[i] = i;
}
//找root，使用路径压缩
int find(int id) {
	if (pr[id] != id) {
		int root = find(pr[id]);
		pr[id] = root;
		return root;
	}
	else
		return id;	//递归边界
}
//
void myunion(int id1,int id2) {
	int root1 = find(id1);
	int root2 = find(id2);
	if (root1 != root2) {
		pr[root2] = root1;
	}
}


int N,Q;
set<int> birds;
set<int> trees;
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int K;
		cin >> K;
		vector<int> vec;
		for (int i = 0; i < K; i++) {
			int x; cin >> x;
			vec.push_back(x);
			birds.insert(x);
		}
		for (int i = 1; i < K; i++) {
			myunion(vec[0], vec[i]);
		}
	}
	cin >> Q;
}





int main(void) {
	ios::sync_with_stdio(false);
	init();
	input();

	//计算树的数量
	for (int i = 0; i < MAX; i++) {
		if (birds.find(i) != birds.end()) {
			int root = find(i);
			trees.insert(root);
		}
	}
	cout << trees.size() << " " << birds.size() << endl;
	for (int i = 0; i < Q; i++) {
		int x, y;
		cin >> x >> y;
		if (find(x) == find(y))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
}

/*
4
3 10 1 2
2 3 4
4 1 5 7 8
3 9 6 4
2
10 5
3 7

*/