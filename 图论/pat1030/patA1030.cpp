#include <cstdio>
#include <cstring>
#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

//用于邻接表
struct edge {
	int id;
	int dist;	//距离
	int cost;	//花费
	edge(int x, int y, int z) :id(x), dist(y), cost(z) {}
};

//用于优先队列
struct vertex {
	int id;
	int d;	//节点到源点的当前最短距离
	vertex(int x, int y) :id(x), d(y) {}
};

//优先队列的比较函数
struct cmp {
	bool operator()(vertex& a, vertex& b) {
		return a.d > b.d;
	}
};


const int MAX = 500;
const int INF = 0x3fffffff;
//节点数，边数，源点，汇点
int N, M, S, D;
//邻接表
vector<edge> adj[MAX];
//判别节点是否已找到最短路径
bool visit[MAX] = { false };
//每个节点当前到源点的最短路径长度
int disto[MAX];
//每个节点在最短路径树上的前驱
set<int> pathto[MAX];
//最短路径
int mindist = 0;
//最小花费
int mincost = INF;
//最优路径
vector<int> path;
vector<int> temppath;


//读输入
void input() {
	cin >> N >> M >> S >> D;
	for (int i = 0; i < M; i++) {
		int u, v, d, c;
		cin >> u >> v >> d >> c;
		adj[u].push_back(edge(v, d, c));
		adj[v].push_back(edge(u, d, c));
	}
}


//找最短路径，存到pathto数组中
void dijkstra() {
	//初始化源点的数据
	visit[S] = true;
	disto[S] = 0;

	priority_queue<vertex, vector<vertex>, cmp> pq;
	pq.push(vertex(S, 0));

	while (true) {
		//当前节点u
		vertex u = pq.top();
		pq.pop();
		int uid = u.id;
		visit[uid] = true;
		int udist = u.d;

		//找到汇点，退出
		if (uid == D)
			break;


		//松弛当前节点
		for (int i = 0; i < adj[uid].size(); i++) {
			int v = adj[uid][i].id;
			if (!visit[v]) {
				if (udist + adj[uid][i].dist < disto[v]) {
					//更新disto与pathto
					disto[v] = udist + adj[uid][i].dist;
					pathto[v].clear();
					pathto[v].insert(uid);
				}
				else if (udist + adj[uid][i].dist == disto[v]) {
					pathto[v].insert(uid);
				}
			}
		}

		//构造优先队列
		pq = priority_queue<vertex, vector<vertex>, cmp>();
		for (int i = 0; i < N; i++) {
			if (!visit[i])
				pq.push(vertex(i, disto[i]));
		}
	}

	mindist = disto[D];
}


//计算temppath的花费
int calcost() {
	int tempcost = 0;
	for (int i = 0; i < temppath.size() - 1; i++) {
		int u = temppath[i], v = temppath[i + 1];
		for (int j = 0; j < adj[u].size(); j++) {
			if (adj[u][j].id == v) {
				tempcost += adj[u][j].cost;
				break;
			}
		}
	}
	return tempcost;
}

//对最短路径树，从u开始向源点DFS，计算最少花费
void DFS(int u) {
	//DFS到了源点
	if (u == S) {
		temppath.push_back(u);
		//计算花费
		int tempcost = calcost();

		//更新path
		if (tempcost < mincost) {
			mincost = tempcost;
			path = temppath;
		}

		temppath.pop_back();
	}
	else {
		temppath.push_back(u);
		for (auto iter = pathto[u].begin(); iter != pathto[u].end(); iter++) {
			DFS(*iter);
		}
		temppath.pop_back();	//记得要把最后一个元素弹出
	}
}



int main(void) {
	input();
	fill(disto, disto + MAX, INF);

	dijkstra();
	DFS(D);

	//输出
	for (int i = path.size() - 1; i >= 0; i--) {
		cout << path[i] << " ";
	}
	cout << mindist << " " << mincost;
	return 0;
}



