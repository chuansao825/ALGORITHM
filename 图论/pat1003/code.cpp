#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>


using namespace std;

//用于邻接表
struct node {
	int id;		//另一点的id
	int w;		//边权
	node(int x,int y):id(x),w(y){}
};	

//用于优先队列
struct vertex {
	int id;
	int d;		//当前到源点的最短距离
	vertex(int x,int y):id(x),d(y){}
};

//优先队列的比较函数
struct cmp {
	bool operator ()(vertex& a, vertex& b) {
		return a.d>b.d;	//最小值优先
	}
};

//INF
const int INF = 0x3fffffff;
//最大节点数 
const int MAX = 500;
//节点数
int N;
//边数
int M;
//源点
int s;
//汇点
int t;
//邻接表
vector<node> adj[MAX];
//各城市救援组数量
int resc[MAX] = { 0 };
//标记节点是否已在最短路径树中
bool visit[MAX] = { false };
//disto数组
int disto[MAX];
//储存当前到各个结点的最短路径数
int pnum[MAX] = { 0 };
//储存当前到每个点的最短路径中的最大点权
int wnum[MAX] = { 0 };


//读输入
void input() {
	cin >> N >> M>>s>>t;
	for (int i = 0; i < N; i++) {
		cin >> resc[i];
	}
	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(node(v, w));
		adj[v].push_back(node(u, w));
	}
}


//求解
void dijkstra() {
	//当前节点的id
	int cid = s;

	//计数器
	int count = N;	

	while (count--) {
		//若当前节点是目标节点，退出
		if (cid == t)
			break;

		//松弛当前节点
		for (int i = 0; i < adj[cid].size(); i++) {
			int v = adj[cid][i].id;
			int w = adj[cid][i].w;

			if (!visit[v] && disto[cid]+w<disto[v]) {
				//更新disto,wnum,pnum三个数组
				disto[v] = disto[cid] + w;
				wnum[v] = resc[v] + wnum[cid];
				pnum[v] = pnum[cid];
				continue;
			}

			if (!visit[v] && disto[cid] + w == disto[v]) {
				//更新wnum,pnum2个数组
				if (wnum[cid] + resc[v] > wnum[v])
					wnum[v] = wnum[cid] + resc[v];
				
				pnum[v] += pnum[cid];
				continue;
			}
		}

		//从pq中选出当前disto值最小的节点作为下一个节点
		//优先队列，使用小根堆
		priority_queue<vertex, vector<vertex>, cmp> pq;
		//将所有没有visit的节点加入优先队列
		for (int i = 0; i < N; i++) {
			if(!visit[i])
				pq.push(vertex(i, disto[i]));
		}
			
		//找到disto值最小的节点，更新cid
		if (pq.size() > 0) {
			cid = pq.top().id;
			//将cid对应的visit置true
			visit[cid] = true;
		}
	}

}



int main(void) {
	fill(disto, disto + MAX, INF);
	input();

	//将disto的源点对应的值设为0，visit设为true，并设置pnum,wnum
	disto[s] = 0;
	visit[s] = true;
	pnum[s] = 1;
	wnum[s] = resc[s];

	//计算
	dijkstra();
	//输出
	cout << pnum[t] << " "<<wnum[t] << endl;

	return 0;
}

