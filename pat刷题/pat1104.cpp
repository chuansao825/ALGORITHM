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
#include<cmath>
using namespace std;
#define ll long double
const int MAX = 100005;
int N;
ll dat[MAX] = { 0 };

void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> dat[i];
	}
}


//DP求解
//dp[i]表示前i个元素的Sum of Number Segments
ll dp[MAX] = { 0 };
//前缀和数组,presum[i]储存数列dat[i]*(i+1)的前i个元素之和
ll presum[MAX] = { 0 };
void DP() {
	for (int i = 0; i < N; i++) {
		presum[i] = dat[i] * (i + 1);
	}
	for (int i = 1; i < N; i++) {
		presum[i] = presum[i - 1] + presum[i];
	}

	dp[0] = dat[0];
	for (int i = 1; i < N; i++) {
		dp[i] = dp[i - 1] + presum[i];
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	input();
	DP();
	printf("%.2llf\n", dp[N - 1]);
}

/*
4
0.1 0.2 0.3 0.4

1
0.1

4
0.4 0.3 0.2 0.1

4
0.2 0.1 0.3 0.4

3
0.1 0.1 0.1

*/