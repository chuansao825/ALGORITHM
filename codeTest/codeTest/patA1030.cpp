#include <cstdio>
#include <cstring>
#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

//�����ڽӱ�
struct edge {
	int id;
	int dist;	//����
	int cost;	//����
	edge(int x, int y, int z) :id(x), dist(y), cost(z) {}
};

//�������ȶ���
struct vertex {
	int id;
	int d;	//�ڵ㵽Դ��ĵ�ǰ��̾���
	vertex(int x, int y) :id(x), d(y) {}
};

//���ȶ��еıȽϺ���
struct cmp {
	bool operator()(vertex& a, vertex& b) {
		return a.d > b.d;
	}
};


const int MAX = 500;
const int INF = 0x3fffffff;
//�ڵ�����������Դ�㣬���
int N, M, S, D;
//�ڽӱ�
vector<edge> adj[MAX];
//�б�ڵ��Ƿ����ҵ����·��
bool visit[MAX] = { false };
//ÿ���ڵ㵱ǰ��Դ������·������
int disto[MAX];
//ÿ���ڵ������·�����ϵ�ǰ��
set<int> pathto[MAX];
//���·��
int mindist = 0;
//��С����
int mincost = INF;
//����·��
vector<int> path;
vector<int> temppath;


//������
void input() {
	cin >> N >> M >> S >> D;
	for (int i = 0; i < M; i++) {
		int u, v, d, c;
		cin >> u >> v >> d >> c;
		adj[u].push_back(edge(v, d, c));
		adj[v].push_back(edge(u, d, c));
	}
}


//�����·�����浽pathto������
void dijkstra() {
	//��ʼ��Դ�������
	visit[S] = true;
	disto[S] = 0;

	priority_queue<vertex, vector<vertex>, cmp> pq;
	pq.push(vertex(S, 0));

	while (true) {
		//��ǰ�ڵ�u
		vertex u = pq.top();
		pq.pop();
		int uid = u.id;
		visit[uid] = true;
		int udist = u.d;

		//�ҵ���㣬�˳�
		if (uid == D)
			break;


		//�ɳڵ�ǰ�ڵ�
		for (int i = 0; i < adj[uid].size(); i++) {
			int v = adj[uid][i].id;
			if (!visit[v]) {
				if (udist + adj[uid][i].dist < disto[v]) {
					//����disto��pathto
					disto[v] = udist + adj[uid][i].dist;
					pathto[v].clear();
					pathto[v].insert(uid);
				}
				else if (udist + adj[uid][i].dist == disto[v]) {
					pathto[v].insert(uid);
				}
			}
		}

		//�������ȶ���
		pq = priority_queue<vertex, vector<vertex>, cmp>();
		for (int i = 0; i < N; i++) {
			if (!visit[i])
				pq.push(vertex(i, disto[i]));
		}
	}

	mindist = disto[D];
}


//����temppath�Ļ���
int calcost() {
	int tempcost = 0;
	for (int i = 0; i < temppath.size() - 1; i++) {
		int u = temppath[i], v = temppath[i + 1];
		for (int j = 0; j < adj[u].size(); j++) {
			if (adj[u][j].id == v) {
				tempcost += adj[u][j].cost;
				break;
			}
		}
	}
	return tempcost;
}

//�����·��������u��ʼ��Դ��DFS���������ٻ���
void DFS(int u) {
	//DFS����Դ��
	if (u == S) {
		temppath.push_back(u);
		//���㻨��
		int tempcost = calcost();

		//����path
		if (tempcost < mincost) {
			mincost = tempcost;
			path = temppath;
		}

		temppath.pop_back();
	}
	else {
		temppath.push_back(u);
		for (auto iter = pathto[u].begin(); iter != pathto[u].end(); iter++) {
			DFS(*iter);
		}
		temppath.pop_back();	//�ǵ�Ҫ�����һ��Ԫ�ص���
	}
}



int main(void) {
	input();
	fill(disto, disto + MAX, INF);

	dijkstra();
	DFS(D);

	//���
	for (int i = path.size() - 1; i >= 0; i--) {
		cout << path[i] << " ";
	}
	cout << mindist << " " << mincost;
	return 0;
}



