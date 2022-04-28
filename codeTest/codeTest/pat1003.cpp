#include<iostream>
#include<queue>
#include<vector>
#include<set>
#include<cstdio>
#include<cstring>

using namespace std;

//用于邻接表
struct edge {
	int id;
	int dist;
	edge(int _id,int _dist):id(_id),dist(_dist){}
};

//存节点的救援组数量
struct node {
	int id;
	int resc;
	node(int _id,int _resc):id(_id),resc(_resc){}
};

const int MAX = 500;
const int INF = 0x3fffffff;
//节点数、边数、源点、汇点
int N, M, S, D;
//邻接表
vector<edge> adj[MAX];
//每个点的救援组
int resc[MAX] = { 0 };
//disTo数组
int disto[MAX];
//pathTo数组
set<int> pathto[MAX];
//判别节点是否在队列中
int inq[MAX] = { false };
//结果
int pathnum = 0, rescnum = 0;
//储存一条最短路径
vector<int> temppath;


void input() {
	cin >> N>>M>>S>> D;
	for (int i = 0; i < N; i++)
		cin >> resc[i];
	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(edge(v,w));
		adj[v].push_back(edge(u, w));
	}
}

//求解最短路径，填充disTo,pathTo
void SPFA() {
	//初始化
	fill(disto, disto + MAX, INF);
	disto[S] = 0;

	//创建队列并将源点加入
	queue<int> q;
	q.push(S);

	//while 队列非空
	while (!q.empty()) {
		//出队一个节点
		int u = q.front();
		q.pop();
		inq[u] = false;

		//松弛该节点,将被松弛的另一端节点加入队列
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].id;
			int dist = adj[u][i].dist;
			if (disto[v] > dist + disto[u]) {
				//松弛边，修改pathto
				disto[v] = dist + disto[u];	
				pathto[v].clear();
				pathto[v].insert(u);

				if (!inq[v]) {
					q.push(v);
					inq[v] = true;
				}					
			}
			else if (disto[v] == dist + disto[u]) {
				//修改pathto
				pathto[v].insert(u);
			}
		}
	}	
}


//计算temppath对应的总救援组数量
int cal() {
	int sum=0;
	for (int i = 0; i < temppath.size(); i++) {
		int u = temppath[i];
		sum += resc[u];
	}
	return sum;
}

//使用DFS计算最短路径数,最大点权值
void DFS(int id) {
	//当前节点是源点
	if (id == S) {
		temppath.push_back(id);
		//计算rescnum
		int sum = cal();
		if (sum > rescnum)	rescnum = sum;
		//更新pathnum
		pathnum++;

		//删除最后一个元素
		temppath.pop_back();
	}

	//当前节点不是源点
	else {
		temppath.push_back(id);
		for (auto iter=pathto[id].begin();iter!=pathto[id].end();iter++) {
			int v = (*iter);
			DFS(v);
		}
		temppath.pop_back();	//记得删除最后一个元素
	}
}

int main(void) {
	input();
	SPFA();
	DFS(D);

	cout << pathnum << " " << rescnum << endl;
}