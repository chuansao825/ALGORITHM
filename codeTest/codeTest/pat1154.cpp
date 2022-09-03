#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<unordered_map>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

const int MAX = 10005;
int N, M,K;
int color[MAX] = { 0 };
map<pair<int,int>, bool> adj;
void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		adj[make_pair(u,v)] = true;
	}
	cin >> K;
}

set<int> s;
void solve() {
	for (int k = 0; k < K; k++) {
		for (int i = 0; i < N; i++) {
			cin >> color[i];
			s.insert(color[i]);
		}
		//检查所有边
		bool flag = true;
		for (auto it = adj.begin(); it != adj.end(); it++) {
			pair<int,int> p = it->first;
			int u = p.first;
			int v = p.second;
			if (color[u] == color[v]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			printf("%d-coloring\n", s.size());
		}
		else {
			cout << "No" << endl;
		}

		//重置数据结构
		fill(color, color + N, 0);
		s.clear();
	}
}

int main(void) {
	input();
	solve();
}

/*
10 11
8 7
6 8
4 5
8 4
8 1
1 2
1 4
9 8
9 1
1 0
2 4
4
0 1 0 1 4 1 0 1 3 0
0 1 0 1 4 1 0 1 0 0
8 1 0 1 4 1 0 5 3 0
1 2 3 4 5 6 7 8 8 9

*/