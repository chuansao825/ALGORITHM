#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 100005;
//����������
int n, m;
//�ڽӱ�,�ڵ��Ŵ�1��ʼ
vector<int> adj[MAX];
//dp����,���浱ǰ�Ըýڵ�Ϊĩβ��ʳ�����ĸ���
int dp[MAX] = { 0 };
//�ڵ����ȡ�����
int ind[MAX] = { 0 };
int outd[MAX] = { 0 };
//�жϽڵ��Ƿ���������
bool inq[MAX] = { false };
//����
int totalnum = 0;



//�����룬�����ڽӱ��ind,outd����
void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		outd[u]++;
		ind[v]++;
	}
}

//ͨ�����������˳�򣬽���DP
void toposort() {
	//���У�����ڵ���
	queue<int> q;

	//�����Ϊ0�ҳ��Ȳ�Ϊ0�Ľڵ��dpֵ��Ϊ1,��push�����
	for (int i = 0; i < n; i++) {
		if (ind[i] == 0 && outd[i] != 0) {
			dp[i] = 1;
			q.push(i);
		}			
	}

	//ѭ��������������
	while (!q.empty()) {
		int cid=q.front();
		q.pop();
		//ɾ������
		for (int i = 0; i < adj[cid].size(); i++) {
			int u = adj[cid][i];
			ind[u]--;
			//�޸�u��dpֵ
			dp[u] += dp[cid];
			//�����������Ϊ0�ĵ�������,���������ս��
			if (ind[u] == 0) {
				q.push(u);
				if (outd[u] == 0)
					totalnum += dp[u];
			}
			
		}
	}
} 


int main(void) {
	input();
	toposort();
	cout << totalnum << endl;
}