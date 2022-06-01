#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<string>
using namespace std;

int P, id,M;

int main(void) {
	//加速IO
	ios::sync_with_stdio(false);

	cin >> P;
	int c = 0;
	while (++c<=P) {
		priority_queue<int, vector<int>, greater<int>> up;	//小根堆
		priority_queue<int, vector<int>, less<int>> down;	//大根堆
		cin >>id>> M;

		cout << id << " " << (M + 1) / 2 << endl;

		int cnt = 0;	//记录已经输出的结果数
		for (int i = 1; i <= M; i++) {
			int x;	cin >> x;
			if (down.size() == 0)	down.push(x);
			else {
				if (x > down.top())
					up.push(x);
				else
					down.push(x);
			}

			if (i % 2 == 0) {
				//平衡两个堆的大小
				if (down.size() != up.size()) {
					up.push(down.top());
					down.pop();
				}
			}
			else {
				if (down.size() < up.size()) {
					down.push(up.top());
					up.pop();
				}
				
				//输出当前中位数
				cout << down.top();
				cnt++;
				if (cnt % 10 == 0 || cnt==(M+1)/2)
					cout << endl;
				else
					cout << " ";
			}
		}
	}
	return 0;
}