#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cstdio>
#include<cmath>

using namespace std;

//树的坐标
struct tree {
	int x;
	int y;
	tree(int _x, int _y) :x(_x), y(_y) {}
	tree() { x = y = 0; }
};



const int MMAX = 505;
const int NMAX = 1005;
const double INF = 10000;
int M, N;
//邻接矩阵
double G[NMAX][NMAX] = { INF };
//判别该点是否已加入到MST中
bool visit[NMAX] = { false };
//每个点到MST的当前最短距离
double disto[NMAX] = { INF };
//猴子的跳跃距离
int jmp[MMAX] = { 0 };
//树的坐标
tree pos[NMAX];
//储存MST中最长的边的长度
double maxlen = 0;



void input() {
	cin >> M;
	for (int i = 0; i < M; i++)
		cin >> jmp[i];
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		pos[i] = tree(x, y);
	}
}


void cal() {
	int x1, y1, x2, y2;
	double w;
	for (int i = 0; i < N; i++) {
		x1 = pos[i].x;
		y1 = pos[i].y;
		for (int j = 0; j <= i; j++) {
			x2 = pos[j].x;
			y2 = pos[j].y;
			w = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			G[i][j] = G[j][i] = w;
		}
	}
}

//用prim算法求解MST
void prim() {
	disto[0] = 0;
	
	//新加入MST的节点
	int cid = 0;
	//已加入MST的节点数
	int count = 0;
	while (true) {
		visit[cid] = true;
		count++;
		if (count == N)	break;

		//松弛节点
		for (int j = 0; j < N; j++) {
			if (visit[j])	continue;
			if (disto[j] > G[cid][j]) {
				disto[j] = G[cid][j];
			}
		}

		//找到与树距离最近的节点
		double temp = INF;
		int id;
		for (int i= 0; i < N; i++) {
			if (visit[i])	continue;
			if (disto[i] < temp) {
				id = i;
				temp = disto[id];
			}
		}
		//更新cid和maxlen
		cid = id;
		if (maxlen < temp)	maxlen = temp;
	}
}

int main(void) {
	fill(disto, disto + NMAX, INF);
	input();
	cal();
	prim();

	int count = 0;
	for (int i = 0; i < M; i++) {
		if (jmp[i] >= maxlen) {
			count++;
		}
	}

	cout << count << endl;
	return 0;
}
