#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cstdio>
#include<cmath>

using namespace std;

//用于kruskal
struct edge {
	int u;
	int v;
	double w;
	edge(int x,int y,double z):u(x),v(y),w(z){}
	edge(){}
};

//树的坐标
struct tree {
	int x;
	int y;
	tree(int _x,int _y):x(_x),y(_y){}
	tree() { x = y = 0; }
};


const int MMAX = 505;
const int NMAX = 1005;
const double INF = 10000;
int M, N;
//完全图中的所有边
vector<edge> edges;
//猴子的跳跃距离
int jmp[MMAX] = { 0 };
//树的坐标
tree pos[NMAX];
//储存MST中最长的边的长度
double maxlen = 0;
//并查集
int uf[NMAX];




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

//预处理
void cal() {
	int x1, y1, x2, y2;
	double w;
	for (int i = 0; i < N; i++) {
		x1 = pos[i].x;
		y1 = pos[i].y;
		for (int j = 0; j < i; j++) {
			x2 = pos[j].x;
			y2 = pos[j].y;			
			w= sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			edges.push_back(edge(i, j, w));
		}
	}
}


//若a，b不连通，就将其所属两个集合union
void unionfind(int a, int b) {
	while (a != uf[a])		a = uf[a];
	while (b != uf[b])		b = uf[b];
	if (a != b)	uf[b] = a;
}

bool connect(int a, int b) {
	while (a != uf[a])		a = uf[a];
	while (b != uf[b])		b = uf[b];
	return a == b;
}


bool cmp(edge a,edge b) {
	return a.w < b.w;
}

//使用kruskal算法求解
void kruskal() {
	//初始化并查集
	for (int i = 0; i < N; i++)
		uf[i] = i;

	//将所有边升序排序
	sort(edges.begin(), edges.end(), cmp);
	//已加入MST的边数
	int count = 0;
	for (int i = 0; i < edges.size(); i++) {
		//先判断边的两个节点是否已经在同一个集合中
		int u = edges[i].u;
		int v = edges[i].v;
		if (connect(u, v))
			continue;

		unionfind(u, v);
		double w = edges[i].w;
		count++;
		if (w > maxlen)		maxlen = w;
		if (count == N - 1)	break;
	}
}




int main(void) {
	input();
	cal();
	kruskal();

	int count = 0;
	for (int i = 0; i < M; i++) {
		if (jmp[i] >= maxlen) {
			count++;
		}			
	}

	cout << count << endl;
	return 0;
}