#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

const int MAX1 = 10005;
const int MAX2 = 105;
int N, M;
//N��Ӳ�ҵ���ֵ
int coin[MAX1] = { 0 };
//dp����,dp[i][j]��ʾ��ǰi��Ӳ��ȡ��Ӳ�ң�������ֵ�����ֵ��С��j
int dp[MAX2] = { 0 };
//������
vector<int> result;
//ÿ�ֵ�ѡ��
int choice[MAX1][MAX2] = { false };

struct cmp {
	bool operator()(int& a, int& b) {
		return a > b;
	}
};

void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		cin >> coin[i];
	//��coin���鰴�ս�������
	sort(coin+1, coin + N+1,cmp());
}


int main(void) {
	ios::sync_with_stdio(false);
	input();

	//DP���,�����������
	for (int i = 1; i <= N; i++) {
		for (int j = M; j >= coin[i]; j--) {
			if (coin[i] + dp[j - coin[i]] >= dp[j]) {
				dp[j] = coin[i] + dp[j - coin[i]];
				choice[i][j] = true;
			}
		}
	}

	//�ж��Ƿ��н�
	if (dp[M] != M)
		cout << "No Solution" << endl;
	else {
		//����̬�������
		int i = N, j = M;
		while (j > 0) {
			if (choice[i][j]) {
				result.push_back(coin[i]);
				j -= coin[i];
				i--;
			}
			else {
				i--;
			}
		}

		for (int i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		cout << endl;
	}
}