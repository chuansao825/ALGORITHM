#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
using namespace std;

struct node {
	int id;
	vector<int> child;	//�����ӽ����
	int level;	//��ȣ���0��ʼ
	node(int a, vector<int> b) { id = a; child = b; level = 0; }
	node(){}
};

int N, M;
const int MAX = 105;
struct node tree[MAX];
bool nonleaf[MAX] = { false };

void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int id, k;
		cin >> id >> k;
		nonleaf[id] = true;
		vector<int> v;
		for (int i = 0; i < k; i++) {
			int temp;
			cin >> temp;
			v.push_back(temp);
		}
		struct node n = node(id, v);
		tree[id] = n;
	}
}



//keyΪlevel��valueΪ��levelҶ�ڵ������
int map1[MAX] = { 0 };
queue<int> q;
int maxlevel = 0;
//���������ؽ���
void create_tree() {
	//int l = 0;
	//int cid = 0;
	q.push(1);
	if (tree[1].child.size() != 0) {
		map1[0] = 0;
	}
	else {
		map1[0] = 1;
	}

	
	while (!q.empty()) {
		int cid = q.front();
		int l = tree[cid].level;
		for (int i = 0; i < tree[cid].child.size(); i++) {
			//����������
			if (l + 1 > maxlevel)
				maxlevel = l + 1;

			int child = tree[cid].child[i];
			//�ж��ӽ���Ƿ�ΪҶ��㲢�ֱ���
			if (nonleaf[child]) {
				tree[child].level = l + 1;
				q.push(child);
			}
			else {
				map1[l + 1]++;
			}
		}
		q.pop();
	}
}


int main(void) {
	ios::sync_with_stdio(false);
	input();
	create_tree();

	for (int i = 0; i <= maxlevel - 1; i++) {
		cout << map1[i] << " ";
	}
	cout << map1[maxlevel]<<endl;

}


/*
2 1
01 1 02

12 5
1 4 2 3 4 5
3 2 6 7
5 3 8 9 10
7 1 11
9 1 12

1 0
*/