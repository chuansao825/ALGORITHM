#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
using namespace std;


const int MAX = 205;
const int MAX2 = 105;
bool adj[MAX][MAX] = {false};
vector<int> arr1[MAX2];
set<int> arr2[MAX2];
int N, M, K;
void input() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		adj[u][v] = adj[v][u] = true;
	}
	cin >> K;
	for (int i = 1; i <= K; i++) {
		int L;
		cin >> L;
		for (int j = 0; j < L; j++) {
			int temp;
			cin >> temp;
			arr1[i].push_back(temp);
			arr2[i].insert(temp);
		}
	}
}

//判断结点是否两两相连
bool iscon(vector<int> v) {
	for (int i = 0; i < v.size()-1; i++) {
		int u1 = v[i];
		for (int j = i + 1; j < v.size(); j++) {
			int u2 = v[j];
			if (!adj[u1][u2])
				return false;
		}
	}
	return true;
}

//判断多个节点是否还有公共的相连结点。有的话返回id，否则返回0
int isfull(vector<int> v,set<int> s) {
	for (int i = 1; i <= N; i++) {
		if (s.find(i) == s.end()) {
			vector<int> tmp = v;
			tmp.push_back(i);
			if (iscon(tmp))
				return i;
		}
	}
	return 0;
}

int main(void) {
	input();
	
	for (int i = 1; i <= K; i++) {
		vector<int> v = arr1[i];
		set<int> s = arr2[i];
		if (iscon(v)) {
			int flag = isfull(v, s);
			if (flag)
				cout << "Area " << i << " may invite more people, such as " << flag << "." << endl;
			else
				cout << "Area " << i << " is OK." << endl;
		}
		else {
			cout << "Area "<<i<<" needs help." << endl;
		}
	}

	return 0;
}

/*
8 10
5 6
7 8
6 4
3 6
4 5
2 3
8 2
2 7
5 3
3 4
6
4 5 4 3 6
3 2 8 7
2 2 3
1 1
2 4 6
3 3 2 1


8 10
5 6
7 8
6 4
3 6
4 5
2 3
8 2
2 7
5 3
3 4
1
2 4 6

*/