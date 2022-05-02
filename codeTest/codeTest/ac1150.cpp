#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include<queue>
#include <limits.h>

using namespace std;
#define ll long long

//�����ڽӱ�
struct node {
	int id;
	ll w;
	node(int x,ll y):id(x),w(y){}
};

const int MAX = 105;
const ll INF = LLONG_MAX;
const int MOD = 100000;
int n, m;
//�ڽӱ�
vector<node> adj[MAX];
//�б�ڵ��Ƿ��ڶ�����
bool inq[MAX] = { false };
ll disto[MAX];
//���鼯
int uf[MAX] = { 0 };
//����DFS
bool visit[MAX] = { false };

//�����������ϵĸ��ڵ���
int root1, root2;
//�б𲢲鼯��a��b�Ƿ���ͬһ��union��
bool connect(int a, int b) {
	while (a != uf[a])		a = uf[a];
	while (b != uf[b])		b = uf[b];
	root1 = a;
	root2 = b;
	return a == b;
}

//�����ݣ���(a^b)%MOD
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

	//��ʼ�����鼯
	for (int i = 0; i < n; i++)
		uf[i] = i;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		if (connect(u, v))
			continue;

		//���������Ϻϲ�
		uf[root2] = root1;

		ll w = qmi(2,i);		
		adj[u].push_back(node(v, w));
		adj[v].push_back(node(u, w));
	}
}

//��DFS���
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