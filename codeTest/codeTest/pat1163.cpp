#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
using namespace std;

struct edge {
	int v;
	int w;
	edge() { v = w = 0; }
	edge(int a, int b) { v = a, w = b; }
};

const int MAX1 = 1005;
const int MAX2 = 105;
vector<edge> adj[MAX1];
vector<vector<int>> SEQ;

int N, M,K;
void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >>w;
		adj[u].push_back(edge(v, w));
		adj[v].push_back(edge(u, w));
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		vector<int> v;
		for (int j = 0; j < N; j++) {
			int tmp;
			cin >> tmp;
			v.push_back(tmp);
		}
		SEQ.push_back(v);
	}
}

//�жϵ�order�������Ƿ���ȷ
bool visit[MAX1] = { false };	//����Ƿ�����·������
int disto[MAX1];
const int INF = 0x3fffffff;
set<int> pre[MAX1];
set<int> set1;
bool judge(int order) {
	vector<int> seq = SEQ[order];
	int s = seq[0];		//Դ��	
	fill(visit, visit + MAX1, false);
	fill(disto, disto + MAX1, INF);
	set1.clear();
	disto[s] = 0;
	for (int i = 1; i <= N; i++) {
		pre[i].clear();
	}
	int u = s;
	int idx = 0;	//ѭ������
	while (true) {
		visit[u] = true;
		//relax
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].v;
			int w = adj[u][i].w;			
			if (disto[v] > disto[u] + w) {
				pre[v].clear();
				pre[v].insert(u);
				disto[v] = disto[u] + w;
			}
			else if (disto[v] == disto[u] + w) {
				pre[v].insert(u);
			}
		}
		//update

		int min = INF;
		for (int i = 1; i <= N; i++) {
			if (!visit[i]) {
				if (disto[i] < min) {
					set1.clear();
					set1.insert(i);
					min = disto[i];
				}
				else if (disto[i] == min) {
					set1.insert(i);
				}
			}
		}
		//�ж�seq����һ�����Ƿ���set1��
		idx++;
		//�ж��˳�
		if (idx >= N)
			break;
		if (set1.find(seq[idx]) == set1.end()) {
			return false;
		}
		else {
			//ȷ����һ����
			u = seq[idx];
		}
	}
	return true;
}


int main(void) {
	input();
	for (int i = 0; i < K; i++) {
		if (judge(i))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
	return 0;
}


/*
5 7
1 2 2
1 5 1
2 3 1
2 4 1
2 5 2
3 5 1
3 4 1
4
5 1 3 4 2
5 3 1 2 4
2 3 4 5 1
3 2 1 5 4

5 7
1 2 2
1 5 1
2 3 1
2 4 1
2 5 2
3 5 1
3 4 1
1
5 3 1 2 4

*/