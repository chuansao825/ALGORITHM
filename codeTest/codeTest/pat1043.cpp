#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

//树的节点
struct node {
	int val;
	struct node* lchild;
	struct node* rchild;
	node(int _val) { val = _val; lchild = rchild = NULL; }
};

const int MAX = 1010;
int N;
//输入序列、先序、镜像BST的先序序列、后序序列
vector<int> seq,pre,pre_m,post;
//BST树根
struct node* Root = NULL;

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a;	cin >> a;
		seq.push_back(a);
	}		
}

//将节点插入BST
void insert(struct node* & root,int val) {
	//找到目标
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

//根据seq创建BST
void create() {
	for (int i = 0; i < N; i++)
		insert(Root, seq[i]);
}

//先序遍历，将序列存在pre数组中
void presearch(struct node* root) {
	if (root == NULL) return;
	pre.push_back(root->val);
	presearch(root->lchild);
	presearch(root->rchild);
}

//镜像树的先序遍历，存在pre_m中
void presearch_m(struct node* root) {
	if (root == NULL)	return;
	pre_m.push_back(root->val);
	presearch_m(root->rchild);
	presearch_m(root->lchild);
}

//后序遍历，存在past中
void postsearch(struct node* root) {
	if (root == NULL)	return;
	postsearch(root->lchild);
	postsearch(root->rchild);
	post.push_back(root->val);
}

//镜像树的后序遍历，存在past中
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

	//判断
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