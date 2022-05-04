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
//��������
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


//ʹ��topo sort�õ��������У�����������Ϊ״ѹDP��˳��
void toposort() {
	queue<int> q;

	//��ʼ�������������Ϊ0�Ľڵ�������
	for (int i = 1; i <= N; i++) {
		if (ind[i] == 0)
			q.push(i);
	}

	//ѭ�����
	while (!q.empty()) {
		int cid = q.front();
		q.pop();
		//���ڵ�ѹջ
		seq.push(cid);	
		for (int i = 0; i < adj[cid].size(); i++) {
			int u = adj[cid][i];
			ind[u]--;
			if (ind[u] == 0)
				q.push(u);
		}
	}
}


//�����������е��������״ѹDP
void dp() {
	while (!seq.empty()) {
		int cid = seq.top();
		seq.pop();
		
		//����ans[cid]
		//����bitset[cid]
		//���Ƚ�cid��Ӧ��bitset����Ӧλ��Ϊ1
		bs[cid].set(cid);
		for (int i = 0; i < adj[cid].size(); i++) {
			int u = adj[cid][i];			
			bs[cid] = bs[cid] | bs[u];
		}
		//bitset[cid]��1�ĸ�������Ϊ��cid�ɴ�Ľڵ���
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