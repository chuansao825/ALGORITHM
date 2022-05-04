#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 100005;
//点数，边数
int n, m;
//邻接表,节点编号从1开始
vector<int> adj[MAX];
//dp数组,储存当前以该节点为末尾的食物链的个数
int dp[MAX] = { 0 };
//节点的入度、出度
int ind[MAX] = { 0 };
int outd[MAX] = { 0 };
//判断节点是否进入过队列
bool inq[MAX] = { false };
//总数
int totalnum = 0;



//读输入，构造邻接表和ind,outd数组
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

//通过拓扑排序的顺序，进行DP
void toposort() {
	//队列，储存节点编号
	queue<int> q;

	//将入度为0且出度不为0的节点的dp值设为1,并push入队列
	for (int i = 0; i < n; i++) {
		if (ind[i] == 0 && outd[i] != 0) {
			dp[i] = 1;
			q.push(i);
		}			
	}

	//循环，找拓扑序列
	while (!q.empty()) {
		int cid=q.front();
		q.pop();
		//删除出边
		for (int i = 0; i < adj[cid].size(); i++) {
			int u = adj[cid][i];
			ind[u]--;
			//修改u的dp值
			dp[u] += dp[cid];
			//将新增的入度为0的点加入队列,并更新最终结果
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