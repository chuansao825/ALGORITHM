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
//标记节点的ans值是否被计算过
bool iscal[MAX] = { false };

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

//使用递归求解,id为当前节点
void solve(int id) {
	bs[id].set(id);
	for (int i = 0; i < adj[id].size(); i++) {
		int u = adj[id][i];
		if(!iscal[u])
			solve(u);
		bs[id] = bs[id] | bs[u];
	}

	ans[id] = bs[id].count();
	iscal[id] = true;
}

int main(void) {
	input();

	//从入度为0的节点开始处理
	for (int i = 1; i < N; i++) {
		if(ind[i]==0)	solve(i);
	}
	
	for (int i = 1; i <= N; i++)
		cout << ans[i] << endl;
}