#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <string.h>

using namespace std;


/*һ���ڵ�*/
struct node {
	int id;		//�ڵ���
	int level;	//BFS�Ĳ���
	node(int x,int y):id(x),level(y){}
};

#define MAX 1010
//������
int N = 0;
//ת������
int L = 0;
//����ѯ���˵�����
int K = 0;
//�ڽӾ��󣬽ڵ��Ŵ�1��ʼ
vector<node> adj[MAX];
//�ڵ��Ƿ���������
bool inq[MAX] = { false };


/*����������*/
void input() {
	cin >> N >> L;
	for (int i = 1; i <= N; i++) {
		//�ڵ��ǰ����n
		int n;
		cin >> n;
		for (int j = 0; j < n; j++) {
			//ǰ���ڵ�ı��x
			int x;
			cin >> x;
			adj[x].push_back(node(i,0));
		}
	}
}



/*��ָ����ŵĽڵ㣬�����ת����*/
int cal(int id) {
	//������
	int cnt = -1;	

	//��id����BFS
	queue<node> q;
	q.push(node(id,0));
	inq[id] = true;
	while (!q.empty()) {
		int cid = q.front().id;	//��ǰջ��id
		node front = q.front();
		q.pop();
		
		//�ж��Ƿ񳬹�����
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
		int j;		//��ǰҪ����Ľڵ�ı��
		cin >> j;
		cout<<cal(j)<<endl;

		//����inq����
		memset(&inq, false, MAX);
	}
	
}
