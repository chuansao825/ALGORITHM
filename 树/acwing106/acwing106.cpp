#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<string>
using namespace std;

int P, id,M;

int main(void) {
	//����IO
	ios::sync_with_stdio(false);

	cin >> P;
	int c = 0;
	while (++c<=P) {
		priority_queue<int, vector<int>, greater<int>> up;	//С����
		priority_queue<int, vector<int>, less<int>> down;	//�����
		cin >>id>> M;

		cout << id << " " << (M + 1) / 2 << endl;

		int cnt = 0;	//��¼�Ѿ�����Ľ����
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
				//ƽ�������ѵĴ�С
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
				
				//�����ǰ��λ��
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