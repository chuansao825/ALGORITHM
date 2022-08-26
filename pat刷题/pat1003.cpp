#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;

struct edge {
	int v;
	int l;
	edge(int _v, int _l) { v = _v; l = _l; }
};

const int MAX = 505;
const int INF = 0x3fffffff;
//邻接表
vector<struct edge> adj[MAX];
//点权
int w[MAX] = { 0 };
int disto[MAX];
set<int> pathto[MAX];
bool visit[MAX] = { false };
int N, M, s, t;

void input() {
	cin >> N >> M >> s >> t;
	for (int i = 0; i < N; i++) {
		cin >> w[i];
	}
	for (int i = 0; i < M; i++) {
		int u, v, l;
		cin >> u >> v >> l;
		adj[u].push_back(edge(v, l));
		adj[v].push_back(edge(u, l));
	}
}

queue<int> q;
bool inqueue[MAX] = { false };
void SPFA() {
	int u = s;
	q.push(u);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		inqueue[u] = false;
		//relax
		for (int i = 0; i < adj[u].size(); i++) {
			struct edge e = adj[u][i];
			int v = e.v;
			int l = e.l;
			if (disto[u] + l < disto[v]) {
				pathto[v].clear();
				pathto[v].insert(u);
				disto[v] = disto[u] + l;

				//入队列
				if (!inqueue[v]) {
					inqueue[v] = true;
					q.push(v);
				}
			}
			else if (disto[u] + l == disto[v]) {
				pathto[v].insert(u);
			}

			
		}
	}
}


vector<int> path;
int maxw = 0;
int mycount = 0;
void DFS(int u, int tempw) {
	path.push_back(u);
	tempw += w[u];
	if (u == s) {
		mycount++;
		if (tempw > maxw)
			maxw = tempw;
		path.pop_back();
		return;
	}

	for (auto it = pathto[u].begin(); it != pathto[u].end(); it++) {
		int pre = *it;
		DFS(pre, tempw);
	}
	path.pop_back();
}


int main(void) {
	ios::sync_with_stdio(false);

	input();
	//初始化
	fill(disto, disto + MAX, INF);
	disto[s] = 0;		//注意

	SPFA();

	//DFS
	DFS(t, 0);
	//output
	cout << mycount << " " << maxw << endl;
	return 0;
}

/*
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1

6 6 5 3
1 1 1 3 1 2
0 1 3
0 3 4
0 5 1
1 2 1
3 4 2
4 5 2


*/



//#include<iostream>
//#include<string>
//#include<cstdio>
//#include<cstring>
//#include<vector>
//#include<set>
//#include<algorithm>
//using namespace std;
//
//struct edge {
//	int v;
//	int l;
//	edge(int _v, int _l) { v = _v; l = _l; }
//};
//
//const int MAX = 505;
//const int INF = 0x3fffffff;
////邻接表
//vector<struct edge> adj[MAX];
////点权
//int w[MAX] = { 0 };
//int disto[MAX];
//set<int> pathto[MAX];
//bool visit[MAX] = { false };
//int N, M,s,t;
//
//void input() {
//	cin >> N >> M>>s>>t;
//	for (int i = 0; i < N; i++) {
//		cin >> w[i];
//	}
//	for (int i = 0; i < M; i++) {
//		int u, v,l;
//		cin >> u >> v>>l;
//		adj[u].push_back(edge(v, l));
//		adj[v].push_back(edge(u, l));
//	}
//}
//
//
//void dijkstra() {
//	int u=s;	//当前结点
//	while (true) {
//		visit[u] = true;
//
//		//边界
//		if (u == t)
//			break;
//
//		//relax
//		for (int i = 0; i < adj[u].size(); i++) {
//			struct edge e = adj[u][i];
//			int v = e.v;
//			int l = e.l;
//			if (disto[u] + l < disto[v]) {
//				disto[v] = disto[u] + l;
//				pathto[v].clear();
//				pathto[v].insert(u);
//			}
//			else if (disto[u] + l == disto[v]) {
//				pathto[v].insert(u);
//			}
//		}
//		//update u
//		int min = INF;
//		for (int i = 0; i < N; i++) {
//			if (!visit[i] && disto[i]<min) {
//				min = disto[i];
//				u = i;
//			}
//		}
//	}
//}
//
//vector<int> path;
//int maxw = 0;
//int mycount = 0;
//void DFS(int u,int tempw) {
//	path.push_back(u);
//	tempw += w[u];
//	if (u == s) {
//		mycount++;
//		if (tempw > maxw)
//			maxw = tempw;
//		path.pop_back();
//		return;
//	}
//
//	for (auto it = pathto[u].begin(); it != pathto[u].end(); it++) {
//		int pre = *it;
//		DFS(pre,tempw);
//	}
//	path.pop_back();
//}
//
//
//int main(void) {
//	ios::sync_with_stdio(false);
//
//	input();
//	//初始化
//	fill(disto, disto + MAX, INF);
//	disto[s] = 0;		//注意
//
//	dijkstra();
//
//	//DFS
//	DFS(t, 0);
//	//output
//	cout << mycount << " " << maxw << endl;
//	return 0;
//}


/*
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1

6 6 5 3
1 1 1 3 1 2
0 1 3
0 3 4
0 5 1
1 2 1
3 4 2
4 5 2


*/