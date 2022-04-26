#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>


using namespace std;

//�����ڽӱ�
struct node {
	int id;		//��һ���id
	int w;		//��Ȩ
	node(int x,int y):id(x),w(y){}
};	

//�������ȶ���
struct vertex {
	int id;
	int d;		//��ǰ��Դ�����̾���
	vertex(int x,int y):id(x),d(y){}
};

//���ȶ��еıȽϺ���
struct cmp {
	bool operator ()(vertex& a, vertex& b) {
		return a.d>b.d;	//��Сֵ����
	}
};

//INF
const int INF = 0x3fffffff;
//���ڵ��� 
const int MAX = 500;
//�ڵ���
int N;
//����
int M;
//Դ��
int s;
//���
int t;
//�ڽӱ�
vector<node> adj[MAX];
//�����о�Ԯ������
int resc[MAX] = { 0 };
//��ǽڵ��Ƿ��������·������
bool visit[MAX] = { false };
//disto����
int disto[MAX];
//���浱ǰ�������������·����
int pnum[MAX] = { 0 };
//���浱ǰ��ÿ��������·���е�����Ȩ
int wnum[MAX] = { 0 };


//������
void input() {
	cin >> N >> M>>s>>t;
	for (int i = 0; i < N; i++) {
		cin >> resc[i];
	}
	for (int i = 0; i < M; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back(node(v, w));
		adj[v].push_back(node(u, w));
	}
}


//���
void dijkstra() {
	//��ǰ�ڵ��id
	int cid = s;

	//������
	int count = N;	

	while (count--) {
		//����ǰ�ڵ���Ŀ��ڵ㣬�˳�
		if (cid == t)
			break;

		//�ɳڵ�ǰ�ڵ�
		for (int i = 0; i < adj[cid].size(); i++) {
			int v = adj[cid][i].id;
			int w = adj[cid][i].w;

			if (!visit[v] && disto[cid]+w<disto[v]) {
				//����disto,wnum,pnum��������
				disto[v] = disto[cid] + w;
				wnum[v] = resc[v] + wnum[cid];
				pnum[v] = pnum[cid];
				continue;
			}

			if (!visit[v] && disto[cid] + w == disto[v]) {
				//����wnum,pnum2������
				if (wnum[cid] + resc[v] > wnum[v])
					wnum[v] = wnum[cid] + resc[v];
				
				pnum[v] += pnum[cid];
				continue;
			}
		}

		//��pq��ѡ����ǰdistoֵ��С�Ľڵ���Ϊ��һ���ڵ�
		//���ȶ��У�ʹ��С����
		priority_queue<vertex, vector<vertex>, cmp> pq;
		//������û��visit�Ľڵ�������ȶ���
		for (int i = 0; i < N; i++) {
			if(!visit[i])
				pq.push(vertex(i, disto[i]));
		}
			
		//�ҵ�distoֵ��С�Ľڵ㣬����cid
		if (pq.size() > 0) {
			cid = pq.top().id;
			//��cid��Ӧ��visit��true
			visit[cid] = true;
		}
	}

}



int main(void) {
	fill(disto, disto + MAX, INF);
	input();

	//��disto��Դ���Ӧ��ֵ��Ϊ0��visit��Ϊtrue��������pnum,wnum
	disto[s] = 0;
	visit[s] = true;
	pnum[s] = 1;
	wnum[s] = resc[s];

	//����
	dijkstra();
	//���
	cout << pnum[t] << " "<<wnum[t] << endl;

	return 0;
}

