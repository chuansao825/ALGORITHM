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
	int lchild, rchild;		//-1表示NULL
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


//根据输入建立静态树,返回根节点的id
int make_tree(int lb,int ub) {
	//递归边界
	if (lb > ub) {
		return -1;
	}

	//找根
	int min = INF;
	int root = 0;
	for (int i = lb; i <= ub; i++) {
		if (inseq[i] < min) {
			min = inseq[i];
			root = i;
		}
	}
	//划分为左右子树
	tree[root].lchild = make_tree(lb, root - 1);
	tree[root].rchild = make_tree(root + 1, ub);
	return root;
}

int main(void) {
	input();
	ROOT=make_tree(0, N - 1);

	//层序遍历
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