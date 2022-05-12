#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

//���Ľڵ�
struct node {
	int val;
	struct node* lchild;
	struct node* rchild;
	node(int _val) { val = _val; lchild = rchild = NULL; }
};

const int MAX = 1010;
int N;
//�������С����򡢾���BST���������С���������
vector<int> seq,pre,pre_m,post;
//BST����
struct node* Root = NULL;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a;	cin >> a;
		seq.push_back(a);
	}		
}

//���ڵ����BST
void insert(struct node* & root,int val) {
	//�ҵ�Ŀ��
	if (root == NULL) {
		root = new struct node(val);
	}
	else if (root->val > val) {
		insert(root->lchild, val);
	}
	else {
		insert(root->rchild, val);
	}
}

//����seq����BST
void create() {
	for (int i = 0; i < N; i++)
		insert(Root, seq[i]);
}

//��������������д���pre������
void presearch(struct node* root) {
	if (root == NULL) return;
	pre.push_back(root->val);
	presearch(root->lchild);
	presearch(root->rchild);
}

//���������������������pre_m��
void presearch_m(struct node* root) {
	if (root == NULL)	return;
	pre_m.push_back(root->val);
	presearch_m(root->rchild);
	presearch_m(root->lchild);
}

//�������������past��
void postsearch(struct node* root) {
	if (root == NULL)	return;
	postsearch(root->lchild);
	postsearch(root->rchild);
	post.push_back(root->val);
}

//�������ĺ������������past��
void postsearch_m(struct node* root) {
	if (root == NULL)	return;
	postsearch_m(root->rchild);
	postsearch_m(root->lchild);
	post.push_back(root->val);
}

int main(void) {
	input();	
	create();
	presearch(Root);
	presearch_m(Root);

	//�ж�
	if (seq == pre || seq == pre_m) {
		cout << "YES" << endl;
		if (seq == pre)	postsearch(Root);
		else    postsearch_m(Root);
		for (int i = 0; i < post.size(); i++) {
			cout << post[i];
			if (i == post.size() - 1)	cout << endl;
			else    cout << " ";
		}
	}
	else {
		cout << "NO" << endl;
	}

	return 0;
}