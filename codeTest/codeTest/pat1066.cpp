#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

//AVL���Ľڵ�
struct node {
	int v;
	int height;	//��nodeΪ���ڵ�������ĸ߶�
	struct node* lchild;
	struct node* rchild;
	node(int _v) { v = _v; height = 1; lchild = rchild = NULL; }
};

const int MAX = 25;
int N;
int num[MAX] = { 0 };
struct node* Root=NULL;	//����

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
}


//��ȡ��ǰ����������
int getHeight(struct node* root) {
	int height = root == NULL ? 0 : root->height;
	return height;
}

//���µ�ǰ����������
void updateHeight(struct node* root) {
	int lheight = getHeight(root->lchild);
	int rheight = getHeight(root->rchild);
	root->height = max(lheight, rheight) + 1;
}

//����
void lo(struct node* &root) {
	struct node* temp = root->rchild;
	root->rchild = temp->lchild;
	temp->lchild = root;
	updateHeight(root); 
	updateHeight(temp);
	root = temp;
}

//����
void ro(struct node* &root){
	struct node* temp = root->lchild;
	root->lchild = temp->rchild;
	temp->rchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

int max(int a, int b) { return a > b ? a : b; }

//���㵱ǰ����ƽ������BF
int getBF(struct node* root) {
	return getHeight(root->lchild)-getHeight(root->rchild);
}

//��AVL������һ���ڵ㣬ע��root������ָ������ã����������𵽸��µ�����
void insert(struct node* &root,int v) {
	//�ݹ�߽�
	if (root == NULL) {
		root = new struct node(v);
		return;
	}

	//ת������
	if (root->v > v) {
		insert(root->lchild, v);

		//���µ�ǰ�����ĸ߶�
		updateHeight(root);
		//�ݹ���ý������жϵ�ǰ�����Ƿ�ʧ��
		int BF = getBF(root);	//ƽ������BF
		//BF==2˵����ǰ�ڵ�Ϊʧ��ڵ�
		if (BF == 2) {
			//�ж���LL����LR
			if (getBF(root->lchild) == 1) {
				//LL����������
				ro(root);
			}
			else if (getBF(root->lchild) == -1) {
				//LR����
				lo(root->lchild);
				ro(root);
			}
		}
	}
	//ת������
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

//����һ��AVL��
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