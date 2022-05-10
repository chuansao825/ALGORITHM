#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 35;
//�ڵ���
int N;
//�������򡢲�α�������
int post[MAX] = { 0 };
int in[MAX] = { 0 };
queue<int> level;

//���е�һ���ڵ�
struct node {
	int id;
	struct node* lchild;
	struct node* rchild;
};
//����һ��node
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

//�������ĸ��ڵ�
struct node* Root = NULL;
//ͨ�������������������й���������������Ϊ��ǰ������Ӧ���еķ�Χ
struct node* create(int postlb,int postub,int inlb,int inub) {
	//�ݹ�߽��ж�
	if (postlb > postub) {
		return NULL;
	}

	//��ǰ�����ĸ��ڵ�id
	int cid = post[postub];
	//�����������ڵ�
	struct node* root = Node(cid);
	//���ڵ���������������е��±�k
	int k;
	for (k = inlb; k <= inub; k++) {
		if (in[k] == cid)	break;
	}
	
	//�����������ݹ鴦��
	int llen = k-inlb;	//�������ڵ���
	root->lchild = create(postlb,postlb+llen-1,inlb,k-1);
	int rlen = inub - k;
	root->rchild = create(postub - rlen, postub - 1, inub - rlen + 1, inub);

	return root;
}

//��BFS�õ���α�������
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