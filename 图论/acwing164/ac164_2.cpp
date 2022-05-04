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
//�ڽӱ��ڵ��Ŵ�1��ʼ
vector<int> adj[MAX];
//��ȣ�����
int ind[MAX] = { 0 };
int outd[MAX] = { 0 };
//����dp������,����Ӹýڵ�����ɴ�Ľڵ���(��������)
int ans[MAX] = { 0 };
//����dp,����ÿ���ڵ��Ӧ��bitset
bitset<MAX> bs[MAX];
//��ǽڵ��ansֵ�Ƿ񱻼����
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

//ʹ�õݹ����,idΪ��ǰ�ڵ�
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

	//�����Ϊ0�Ľڵ㿪ʼ����
	for (int i = 1; i < N; i++) {
		if(ind[i]==0)	solve(i);
	}
	
	for (int i = 1; i <= N; i++)
		cout << ans[i] << endl;
}