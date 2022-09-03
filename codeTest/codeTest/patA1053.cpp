#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

//�ڵ�
struct node {
	int id;
	int w;
	//�ӽڵ㣬����wֵ����洢
	vector<int> child;
};

const int MAX = 105;
int N, M, S;
struct node tree[MAX];
//����·��
vector<vector<int>> path;

void input() {
	cin >> N >> M >> S;
	for (int i = 0; i < N; i++) {
		tree[i].id = i;
		int w;	cin >> w;
		tree[i].w = w;
	}

	for (int i = 0; i < M ; i++) {
		int r, n;	cin >> r >> n;
		for (int i = 0; i < n; i++) {
			int c;	cin >> c;
			tree[r].child.push_back(c);
		}
	}
}

//ͨ��DFS��⣬ʹ�ü�֦
int len = 0;	//���浱ǰDFS����·����Ȩ��
vector<int> cp;	//��ǰ·��
void DFS(int id) {
	cp.push_back(tree[id].w);
	//����len
	len += tree[id].w;

	//�ݹ�߽��ж�--�Ѿ�����Ŀ��
	if (len >= S && tree[id].child.size() > 0) {
		cp.pop_back();
		len -= tree[id].w;
		return;
	}
	//�ݹ�߽��ж�--�ҵ�Ŀ��·��
	if (len == S && tree[id].child.size() == 0) {
		path.push_back(cp);
	}

	for (int i = 0; i < tree[id].child.size(); i++) {
		DFS(tree[id].child[i]);
	}

	cp.pop_back();
	len -= tree[id].w;
	return;
}




int main(void) {
	input();
	DFS(0);

	//��·������
	sort(path.begin(), path.end(), greater<vector<int>>());

	for (int i = 0; i < path.size();i++) {
		vector<int> p=path[i];
		for (int i = 0; i < p.size(); i++) {
			cout << p[i];
			if (i == p.size() - 1)	cout << endl;
			else    cout << " ";
		}
	}

	return 0;
}