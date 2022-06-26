#include<cstring>
#include<cstdio>
#include<string>
#include<iostream>
#include<vector>
using namespace std;

const int MAX1 = 205;
const int MAX2 = 10005;
int N, M, L;
int dp[MAX1][MAX2] = { 0 };
//标记第i个颜色是否为喜欢的
bool like[MAX1] = { false };
//储存去掉不喜欢的颜色后的色带
vector<int> mydata;
//储存喜欢的色带
int order[MAX1] = { 0 };


void input() {
	cin >> N;
	cin >> M;
	for (int i = 1; i <= M; i++) {
		int j; cin >> j;
		like[j] = true;
		order[i] = j;
	}
	cin >> L;
	mydata.push_back(0);
	for (int i = 0; i < L; i++) {
		int j; cin >> j;
		if (like[j])	mydata.push_back(j);
	}
}


int main(void) {
	ios::sync_with_stdio(false);

	input();

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j < mydata.size(); j++) {
			if (order[i] == mydata[j]) {
				dp[i][j]=max(dp[i-1][j],dp[i][j-1])+1;
			}
			else {
				dp[i][j]= max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	cout << dp[M][mydata.size()-1] << endl;
}
