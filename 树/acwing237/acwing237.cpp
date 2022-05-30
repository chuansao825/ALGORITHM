#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<unordered_map>		
#include<vector>

using namespace std;

int t;
//使用哈希表离散化储存数据,key为结点编号，value为父结点的编号，注意，每轮循环结束要clear
unordered_map<int, int> father;
//储存当前判定的所有不等于条件，注意，每轮循环结束要clear
vector<pair<int, int>> neq;


//使用路径压缩
int findfather(int i) {
	if (father[i] == i)	return i;
	int root = findfather(father[i]);
	father[i] = root;
	return root;
}

//判断两个节点是否在同一个set中
bool find(int i,int j) {
	return findfather(i) == findfather(j);
}

//union两个set
void myunion(int i,int j) {
	if (!find(i, j)) {
		int r1, r2;
		r1 = findfather(i);
		r2 = findfather(j);
		father[r2] = r1;
	}
}

//将i，j加入father，若已存在则不处理，否则将其加入并初始化
void add(int i, int j) {
	if (father.find(i) == father.end()) {
		father.insert(pair<int, int>(i, i));
	}
	if (father.find(j) == father.end()) {
		father.insert(pair<int, int>(j, j));
	}
}

int main(void) {
	//关闭同步，加速io
	ios::sync_with_stdio(false);

	cin >> t;
	while (t-- > 0) {
		//条件数
		int qnum;
		cin >> qnum;
		int i, j, e;
		while (qnum-- > 0) {
			cin >> i >> j >> e;
			if (e == 1) {
				//先离散化储存，然后union
				add(i, j);
				myunion(i, j);
			}
			else if (e == 0) {
				//先离散化储存，然后存储不相等的数据
				add(i, j);
				neq.push_back(pair<int, int>(i, j));
			}
		}

		//遍历所有不等于的条件，判断节点是否在一个set中
		bool flag=true;
		for (int k = 0; k < neq.size(); k++) {
			int i, j;
			i = neq[k].first;
			j = neq[k].second;
			if (find(i, j)) {
				flag = false;
				break;
			}
		}

		if (flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;

		//清空father，neq容器
		father.clear();
		neq.clear();
	}
}
