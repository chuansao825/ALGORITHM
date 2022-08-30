#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
#include<unordered_map>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

const int MAX = 1005;
int K;
bool chess[MAX][MAX] = { false };
void input() {
	cin >> K;
}

bool judge(int N, set<pair<int, int>> q) {
	for (auto it = q.begin(); it != q.end(); it++) {
		pair<int, int> pos = *it;
		int x = pos.first;
		int y = pos.second;
		//检查行
		for (int i = 1; i <= N; i++) {
			if (i == y)
				continue;
			if (chess[x][i])
				return false;
		}

		//检查主对角线
		int i = x - 1, j = y - 1;
		while (true) {
			if (i < 1 || j < 1)
				break;
			if (chess[i][j])
				return false;
			i--, j--;
		}
		i = x + 1, j = y + 1;
		while (true) {
			if (i > N || j > N)
				break;
			if (chess[i][j])
				return false;
			i++, j++;
		}
		//检查副对角线
		i = x - 1, j = y + 1;
		while (true) {
			if (j > N || i < 1)
				break;
			if (chess[i][j])
				return false;
			i--, j++;
		}
		i = x + 1, j = y - 1;
		while (true) {
			if (i > N || j < 1)
				break;
			if (chess[i][j])
				return false;
			i++, j--;
		}
	}
	return true;
}

int main(void) {
	input();
	for (int i = 0; i < K; i++) {
		int N;
		cin >> N;
		set<pair<int, int>> q;
		for (int j = 1; j <= N; j++) {
			int k = 0;
			cin >> k;
			chess[k][j] = true;
			q.insert(make_pair(k, j));
		}

		if (judge(N, q))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;


		//重置
		fill(chess[0], chess[0] + MAX*MAX, false);
	}
}


/*
4
8 4 6 8 2 7 1 3 5
9 4 6 7 2 8 1 9 5 3
6 1 5 2 6 4 3
5 1 3 5 2 4

*/