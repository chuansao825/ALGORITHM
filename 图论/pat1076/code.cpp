#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <string.h>

using namespace std;


/*一个节点*/
struct node {
	int id;		//节点编号
	int level;	//BFS的层数
	node(int x,int y):id(x),level(y){}
};

#define MAX 1010
//总人数
int N = 0;
//转发层数
int L = 0;
//被查询的人的数量
int K = 0;
//邻接矩阵，节点编号从1开始
vector<node> adj[MAX];
//节点是否进入过队列
bool inq[MAX] = { false };


/*读部分输入*/
void input() {
	cin >> N >> L;
	for (int i = 1; i <= N; i++) {
		//节点的前驱数n
		int n;
		cin >> n;
		for (int j = 0; j < n; j++) {
			//前驱节点的编号x
			int x;
			cin >> x;
			adj[x].push_back(node(i,0));
		}
	}
}



/*对指定编号的节点，求最大转发数*/
int cal(int id) {
	//计数器
	int cnt = -1;	

	//对id进行BFS
	queue<node> q;
	q.push(node(id,0));
	inq[id] = true;
	while (!q.empty()) {
		int cid = q.front().id;	//当前栈顶id
		node front = q.front();
		q.pop();
		
		//判断是否超过层数
		if ( front.level> L)
			break;

		cnt++;

		for (int i = 0; i < adj[cid].size(); i++) {
			int v = adj[cid][i].id;
			if (!inq[v]) {							
				inq[v] = true;
				q.push(node(v, front.level + 1));
			}
		}
	}

	return cnt;
}


int main(void) {
	input();
	
	cin >> K;
	for (int i = 0; i < K; i++) {
		int j;		//当前要计算的节点的编号
		cin >> j;
		cout<<cal(j)<<endl;

		//重置inq数组
		memset(&inq, false, MAX);
	}
	
}
