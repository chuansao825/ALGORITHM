#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

//AVL树的节点
struct node {
	int v;
	int height;	//以node为根节点的子树的高度
	struct node* lchild;
	struct node* rchild;
	node(int _v) { v = _v; height = 1; lchild = rchild = NULL; }
};

const int MAX = 25;
int N;
int num[MAX] = { 0 };
struct node* Root=NULL;	//树根

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
}


//获取当前子树的树高
int getHeight(struct node* root) {
	int height = root == NULL ? 0 : root->height;
	return height;
}

//更新当前子树的树高
void updateHeight(struct node* root) {
	int lheight = getHeight(root->lchild);
	int rheight = getHeight(root->rchild);
	root->height = max(lheight, rheight) + 1;
}

//左旋
void lo(struct node* &root) {
	struct node* temp = root->rchild;
	root->rchild = temp->lchild;
	temp->lchild = root;
	updateHeight(root); 
	updateHeight(temp);
	root = temp;
}

//右旋
void ro(struct node* &root){
	struct node* temp = root->lchild;
	root->lchild = temp->rchild;
	temp->rchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

int max(int a, int b) { return a > b ? a : b; }

//计算当前结点的平衡因子BF
int getBF(struct node* root) {
	return getHeight(root->lchild)-getHeight(root->rchild);
}

//向AVL树插入一个节点，注意root必须是指针的引用，这样才能起到更新的作用
void insert(struct node* &root,int v) {
	//递归边界
	if (root == NULL) {
		root = new struct node(v);
		return;
	}

	//转左子树
	if (root->v > v) {
		insert(root->lchild, v);

		//更新当前子树的高度
		updateHeight(root);
		//递归调用结束后判断当前子树是否失衡
		int BF = getBF(root);	//平衡因子BF
		//BF==2说明当前节点为失衡节点
		if (BF == 2) {
			//判断是LL还是LR
			if (getBF(root->lchild) == 1) {
				//LL型树，右旋
				ro(root);
			}
			else if (getBF(root->lchild) == -1) {
				//LR型树
				lo(root->lchild);
				ro(root);
			}
		}
	}
	//转右子树
	else {
		insert(root->rchild, v);
		updateHeight(root);
		int BF = getBF(root);
		if (BF == -2) {
			if (getBF(root->rchild)==-1) {
				lo(root);
			}
			else if (getBF(root->rchild) == 1) {
				ro(root->rchild);
				lo(root);
			}
		}
	}
}

//创建一棵AVL树
void create() {
	for (int i = 0; i < N; i++) {
		insert(Root, num[i]);
	}
}

int main(void) {
	input();
	create();
	cout << Root->v << endl;
}