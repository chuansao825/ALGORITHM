#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<bitset>
#include<stack>

using namespace std;


const int MAX = 30005;
int N, M;
//邻接表，节点编号从1开始
vector<int> adj[MAX];
//入度，出度
int ind[MAX] = { 0 };
int outd[MAX] = { 0 };
//用于dp的数组,储存从该节点出发可达的节点数(包括自身)
int ans[MAX] = { 0 };
//用于dp,储存每个节点对应的bitset
bitset<MAX> bs[MAX];
//拓扑序列
stack<int> seq;



void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		outd[u]++;
		ind[v]++;
	}
}


//使用topo sort得到拓扑序列，拓扑序列作为状压DP的顺序
void toposort() {
	queue<int> q;

	//初始化，将所有入度为0的节点加入队列
	for (int i = 1; i <= N; i++) {
		if (ind[i] == 0)
			q.push(i);
	}

	//循环求解
	while (!q.empty()) {
		int cid = q.front();
		q.pop();
		//将节点压栈
		seq.push(cid);	
		for (int i = 0; i < adj[cid].size(); i++) {
			int u = adj[cid][i];
			ind[u]--;
			if (ind[u] == 0)
				q.push(u);
		}
	}
}


//根据拓扑序列的逆序进行状压DP
void dp() {
	while (!seq.empty()) {
		int cid = seq.top();
		seq.pop();
		
		//计算ans[cid]
		//先求bitset[cid]
		//首先将cid对应的bitset的相应位置为1
		bs[cid].set(cid);
		for (int i = 0; i < adj[cid].size(); i++) {
			int u = adj[cid][i];			
			bs[cid] = bs[cid] | bs[u];
		}
		//bitset[cid]中1的个数，即为从cid可达的节点数
		ans[cid] = bs[cid].count();
	}
}


int main(void) {
	input();
	fill(ans, ans + MAX, 1);
	toposort();
	dp();

	for (int i = 1; i <= N; i++)
		cout << ans[i] << endl;
}