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
//N个硬币的面值
int coin[MAX1] = { 0 };
//dp数组,dp[i][j]表示从前i个硬币取出硬币，其总面值的最大值且小于j
int dp[MAX2] = { 0 };
//储存结果
vector<int> result;
//每轮的选择
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
	//将coin数组按照降序排序
	sort(coin+1, coin + N+1,cmp());
}


int main(void) {
	ios::sync_with_stdio(false);
	input();

	//DP求解,自右向左更新
	for (int i = 1; i <= N; i++) {
		for (int j = M; j >= coin[i]; j--) {
			if (coin[i] + dp[j - coin[i]] >= dp[j]) {
				dp[j] = coin[i] + dp[j - coin[i]];
				choice[i][j] = true;
			}
		}
	}

	//判断是否有解
	if (dp[M] != M)
		cout << "No Solution" << endl;
	else {
		//从终态倒推求解
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