#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

struct node {
	int id;
	int data;
	int lchild, rchild;		//-1��ʾNULL
	node(){}
	node(int _id,int _data):id(_id),data(_data){}
};
const int MAX = 35;
const int INF = 0x3fffffff;
int N;
int inseq[MAX] = { 0 };
int ROOT = 0;
struct node tree[MAX];
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> inseq[i];
		tree[i] = node(i,inseq[i]);
	}
}


//�������뽨����̬��,���ظ��ڵ��id
int make_tree(int lb,int ub) {
	//�ݹ�߽�
	if (lb > ub) {
		return -1;
	}

	//�Ҹ�
	int min = INF;
	int root = 0;
	for (int i = lb; i <= ub; i++) {
		if (inseq[i] < min) {
			min = inseq[i];
			root = i;
		}
	}
	//����Ϊ��������
	tree[root].lchild = make_tree(lb, root - 1);
	tree[root].rchild = make_tree(root + 1, ub);
	return root;
}

int main(void) {
	input();
	ROOT=make_tree(0, N - 1);

	//�������
	queue<struct node> q;
	vector<int> result;
	q.push(tree[ROOT]);
	while (!q.empty()) {
		struct node n = q.front();
		q.pop();
		if (n.lchild != -1)
			q.push(tree[n.lchild]);
		if (n.rchild != -1)
			q.push(tree[n.rchild]);
		result.push_back(n.data);
	}

	for (int i = 0; i < result.size(); i++) {
		cout << result[i];
		if (i == result.size() - 1)
			cout << endl;
		else
			cout << " ";
	}
}


/*
10
8 15 3 4 1 5 12 10 18 6

*/