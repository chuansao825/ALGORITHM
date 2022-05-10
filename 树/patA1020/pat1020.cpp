#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 35;
//节点数
int N;
//后序、中序、层次遍历序列
int post[MAX] = { 0 };
int in[MAX] = { 0 };
queue<int> level;

//树中的一个节点
struct node {
	int id;
	struct node* lchild;
	struct node* rchild;
};
//创建一个node
struct node* Node(int id) {
	struct node* n = new struct node;
	n->id = id;
	n->lchild = n->rchild = NULL;
	return n;
}

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> post[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> in[i];
	}
}

//二叉树的根节点
struct node* Root = NULL;
//通过后序序列与中序序列构建二叉树，参数为当前子树对应序列的范围
struct node* create(int postlb,int postub,int inlb,int inub) {
	//递归边界判断
	if (postlb > postub) {
		return NULL;
	}

	//当前子树的根节点id
	int cid = post[postub];
	//创建子树根节点
	struct node* root = Node(cid);
	//根节点在中序遍历序列中的下标k
	int k;
	for (k = inlb; k <= inub; k++) {
		if (in[k] == cid)	break;
	}
	
	//对左右子树递归处理
	int llen = k-inlb;	//左子树节点数
	root->lchild = create(postlb,postlb+llen-1,inlb,k-1);
	int rlen = inub - k;
	root->rchild = create(postub - rlen, postub - 1, inub - rlen + 1, inub);

	return root;
}

//用BFS得到层次遍历序列
void BFS() {
	queue<struct node*> q;
	q.push(Root);

	while (!q.empty()) {
		struct node* n = q.front();
		int cid = n->id;
		q.pop();
		level.push(cid);
		
		if (n->lchild != NULL)		q.push(n->lchild);
		if (n->rchild != NULL)		q.push(n->rchild);	
	}
}

int main(void) {
	input();
	Root = create(0,N-1,0,N-1);
	BFS();

	int count = 0;
	while (!level.empty()) {
		cout << level.front();
		level.pop();
		if (++count == N)
			break;
		cout << " ";
	}

	return 0;
}