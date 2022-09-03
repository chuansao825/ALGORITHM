#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

//节点
struct node {
	int id;
	int w;
	//子节点，按照w值降序存储
	vector<int> child;
};

const int MAX = 105;
int N, M, S;
struct node tree[MAX];
//储存路径
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

//通过DFS求解，使用剪枝
int len = 0;	//储存当前DFS到的路径的权重
vector<int> cp;	//当前路径
void DFS(int id) {
	cp.push_back(tree[id].w);
	//更新len
	len += tree[id].w;

	//递归边界判断--已经超出目标
	if (len >= S && tree[id].child.size() > 0) {
		cp.pop_back();
		len -= tree[id].w;
		return;
	}
	//递归边界判断--找到目标路径
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

	//对路径排序
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