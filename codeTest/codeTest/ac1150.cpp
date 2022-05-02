#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include<queue>
#include <limits.h>

using namespace std;
#define ll long long

//用于邻接表
struct node {
	int id;
	ll w;
	node(int x,ll y):id(x),w(y){}
};

const int MAX = 105;
const ll INF = LLONG_MAX;
const int MOD = 100000;
int n, m;
//邻接表
vector<node> adj[MAX];
//判别节点是否在队列中
bool inq[MAX] = { false };
ll disto[MAX];
//并查集
int uf[MAX] = { 0 };
//用于DFS
bool visit[MAX] = { false };

//储存两个集合的根节点编号
int root1, root2;
//判别并查集中a和b是否在同一个union中
bool connect(int a, int b) {
	while (a != uf[a])		a = uf[a];
	while (b != uf[b])		b = uf[b];
	root1 = a;
	root2 = b;
	return a == b;
}

//快速幂，求(a^b)%MOD
ll qmi(ll a, ll b) {
	ll ans = 1, base = a;
	while (b != 0) {
		if ((b & 1) != 0)
			ans = ans * base % MOD;
		base = base * base % MOD;
		b = b >> 1;
	}

	return ans;
}

void input() {
	cin >> n >> m;

	//初始化并查集
	for (int i = 0; i < n; i++)
		uf[i] = i;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		if (connect(u, v))
			continue;

		//将两个集合合并
		uf[root2] = root1;

		ll w = qmi(2,i);		
		adj[u].push_back(node(v, w));
		adj[v].push_back(node(u, w));
	}
}

//用DFS求解
void DFS(int id,ll dist) {
	visit[id] = true;
	for(int i = 0; i < adj[id].size(); i++) {
		int v = adj[id][i].id;
		int w = adj[id][i].w;
		if (!visit[v]) {
			disto[v] = dist + w;
			DFS(v,disto[v]);
		}
		
	}
}

int main(void) {
	input();
	fill(disto, disto + MAX, INF);
	DFS(0,0);
	for (int i = 1; i < n; i++) {
		if (disto[i] == INF)
			cout << "-1" << endl;
		else
			cout << disto[i]% MOD << endl;
	}

	return 0;
}