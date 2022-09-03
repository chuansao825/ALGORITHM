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
	vector<int> child;
	node(vector<int> b):child(b){}
	node(){}
};
const int MAX = 105;
int N,M,W;
int weight[MAX] = { 0 };
node tree[MAX];
void input() {
	cin >> N >> M >>W;
	for (int i = 0; i < N; i++)
		cin >> weight[i];
	for (int i = 0; i < M; i++) {
		int id,k;
		cin >> id >> k;
		vector<int> vec;
		for (int j = 0; j < k; j++) {
			int x; cin >> x;
			vec.push_back(x);
		}
		tree[id] = node(vec);
	}
}

vector<vector<int>> result;
vector<int> path;
void DFS(int root,int w) {
	w = w + weight[root];
	//¼ôÖ¦
	if (w > W) {
		return;
	}

	path.push_back(weight[root]);
	//µÝ¹é±ß½ç
	if (tree[root].child.size() == 0) {
		if (w == W)
			result.push_back(path);
		path.pop_back();
		return;
	}

	vector<int>& vec = tree[root].child;
	for (int i = 0; i < vec.size(); i++) {
		DFS(vec[i],w);
	}
	path.pop_back();
}

int main(void) {
	input();
	DFS(0,0);
	sort(result.begin(), result.end(), greater<vector<int>>());
	for (auto it = result.begin(); it != result.end(); it++) {
		vector<int> vec = *it;
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i];
			if (i == vec.size() - 1)
				cout << endl;
			else
				cout << " ";
		}
	}
}


/*
20 9 24
10 2 4 3 5 10 2 18 9 7 2 2 1 3 12 1 8 6 2 2
00 4 01 02 03 04
02 1 05
04 2 06 07
03 3 11 12 13
06 1 09
07 2 08 10
16 1 15
13 3 14 16 17
17 2 18 19

*/