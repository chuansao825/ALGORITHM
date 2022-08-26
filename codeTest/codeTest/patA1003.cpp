#include<iostream>
#include<queue>
#include<vector>
#include<set>
#include<cstdio>
#include<cstring>

using namespace std;

//�����ڽӱ�
struct edge {
	int id;
	int dist;
	edge(int _id,int _dist):id(_id),dist(_dist){}
};

//��ڵ�ľ�Ԯ������
struct node {
	int id;
	int resc;
	node(int _id,int _resc):id(_id),resc(_resc){}
};

const int MAX = 500;
const int INF = 0x3fffffff;
//�ڵ�����������Դ�㡢���
int N, M, S, D;
//�ڽӱ�
vector<edge> adj[MAX];
//ÿ����ľ�Ԯ��
int resc[MAX] = { 0 };
//disTo����
int disto[MAX];
//pathTo����
set<int> pathto[MAX];
//�б�ڵ��Ƿ��ڶ�����
int inq[MAX] = { false };
//���
int pathnum = 0, rescnum = 0;
//����һ�����·��
vector<int> temppath;


void input() {
	cin >> N>>M>>S>> D;
	for (int i = 0; i < N; i++)
		cin >> resc[i];
	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(edge(v,w));
		adj[v].push_back(edge(u, w));
	}
}

//������·�������disTo,pathTo
void SPFA() {
	//��ʼ��
	fill(disto, disto + MAX, INF);
	disto[S] = 0;

	//�������в���Դ�����
	queue<int> q;
	q.push(S);

	//while ���зǿ�
	while (!q.empty()) {
		//����һ���ڵ�
		int u = q.front();
		q.pop();
		inq[u] = false;

		//�ɳڸýڵ�,�����ɳڵ���һ�˽ڵ�������
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].id;
			int dist = adj[u][i].dist;
			if (disto[v] > dist + disto[u]) {
				//�ɳڱߣ��޸�pathto
				disto[v] = dist + disto[u];	
				pathto[v].clear();
				pathto[v].insert(u);

				if (!inq[v]) {
					q.push(v);
					inq[v] = true;
				}					
			}
			else if (disto[v] == dist + disto[u]) {
				//�޸�pathto
				pathto[v].insert(u);
			}
		}
	}	
}


//����temppath��Ӧ���ܾ�Ԯ������
int cal() {
	int sum=0;
	for (int i = 0; i < temppath.size(); i++) {
		int u = temppath[i];
		sum += resc[u];
	}
	return sum;
}

//ʹ��DFS�������·����,����Ȩֵ
void DFS(int id) {
	//��ǰ�ڵ���Դ��
	if (id == S) {
		temppath.push_back(id);
		//����rescnum
		int sum = cal();
		if (sum > rescnum)	rescnum = sum;
		//����pathnum
		pathnum++;

		//ɾ�����һ��Ԫ��
		temppath.pop_back();
	}

	//��ǰ�ڵ㲻��Դ��
	else {
		temppath.push_back(id);
		for (auto iter=pathto[id].begin();iter!=pathto[id].end();iter++) {
			int v = (*iter);
			DFS(v);
		}
		temppath.pop_back();	//�ǵ�ɾ�����һ��Ԫ��
	}
}

int main(void) {
	input();
	SPFA();
	DFS(D);

	cout << pathnum << " " << rescnum << endl;
}