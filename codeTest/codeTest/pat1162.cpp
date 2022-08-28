#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

struct node {
	int id;		//从1开始
	string data;
	int lchild;
	int rchild;
	node(string a,int b,int c):data(a),lchild(b),rchild(c){ id = 0; }
	node() { id = 0; lchild = rchild = -1; }
};


const int MAX = 25;
int N;
int ROOT=0;
struct node tree[MAX];	//从1开始储存,index为id
void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		string a;
		int b, c;
		cin >> a >> b >> c;
		struct node n = node(a, b, c);
		n.id = i;
		tree[i] = n;
	}
}

//找到树的根
void findroot() {
	//判断child域中没有出现的编号即为结ROOT
	bool f[MAX] = { false };
	for (int i = 1; i <= N; i++) {
		int a = tree[i].lchild;
		int b = tree[i].rchild;
		if (a != -1)
			f[a] = true;
		if (b != -1)
			f[b] = true;
	}
	for (int i = 1; i <= N; i++) {
		if (!f[i])
			ROOT = i;
	}
}

//递归求解
string getexpression(int root) {
	//递归边界
	if (root == -1)
		return "";

	//递推
	string str1 = getexpression(tree[root].lchild);
	string str2 = getexpression(tree[root].rchild);
	//对负号特殊处理
	//题目中没有说明减号出现，但第五个test point出现了所以要处理
	string d = tree[root].data;
	if (tree[root].lchild == -1 && tree[root].rchild != -1) {
		return string("(")+d + str2+")";
	}
	else if(tree[root].lchild==-1 && tree[root].rchild==-1) {
		return "(" + d + ")";
	}
	else
		return "(" + str1 + str2 + d + ")";
}


int main(void) {
	input();
	findroot();
	cout << getexpression(ROOT) << endl;
	return 0;
}



/*
8
* 8 7
a -1 -1
* 4 1
+ 2 5
b -1 -1
d -1 -1
- -1 6
c -1 -1


8
2.35 -1 -1
* 6 1
- -1 4
% 7 8
+ 2 3
a -1 -1
str -1 -1
871 -1 -1

*/