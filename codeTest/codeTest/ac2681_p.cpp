#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cstdio>
#include<cmath>

using namespace std;

//��������
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
//�ڽӾ���
double G[NMAX][NMAX] = { INF };
//�б�õ��Ƿ��Ѽ��뵽MST��
bool visit[NMAX] = { false };
//ÿ���㵽MST�ĵ�ǰ��̾���
double disto[NMAX] = { INF };
//���ӵ���Ծ����
int jmp[MMAX] = { 0 };
//��������
tree pos[NMAX];
//����MST����ıߵĳ���
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

//��prim�㷨���MST
void prim() {
	disto[0] = 0;
	
	//�¼���MST�Ľڵ�
	int cid = 0;
	//�Ѽ���MST�Ľڵ���
	int count = 0;
	while (true) {
		visit[cid] = true;
		count++;
		if (count == N)	break;

		//�ɳڽڵ�
		for (int j = 0; j < N; j++) {
			if (visit[j])	continue;
			if (disto[j] > G[cid][j]) {
				disto[j] = G[cid][j];
			}
		}

		//�ҵ�������������Ľڵ�
		double temp = INF;
		int id;
		for (int i= 0; i < N; i++) {
			if (visit[i])	continue;
			if (disto[i] < temp) {
				id = i;
				temp = disto[id];
			}
		}
		//����cid��maxlen
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
