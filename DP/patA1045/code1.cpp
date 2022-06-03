#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<set>
using namespace std;

const int MAX = 10010;
const int MAX2 = 205;
int N, M, L;
//newl储存去掉所有不喜欢的颜色后的色带元素个数
int newl;
//key为一个喜欢的颜色，value为顺序在key之前的其他颜色
bool map1[MAX2][MAX2] = { false };
//储存去掉不喜欢颜色后的色带
vector<int> dat;
//储存喜欢的颜色
vector<int> color;
set<int> colorset;

void input() {
	cin >> N;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int c; cin >> c; color.push_back(c); colorset.insert(c);
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int c; cin >> c;
		if (colorset.find(c) != colorset.end()) {
			dat.push_back(c);
		}
	}
}

//创建映射
void createmap() {
	for (int i = 0; i < color.size(); i++) {
		int key = color[i];
		for (int j = 0; j <= i; j++) {
			map1[key][color[j]] = true;
		}
	}
}

int dp[MAX] = { 0 };
int main(void) {
	ios::sync_with_stdio(false);
	input();
	createmap();

	//dp求解,dp[i]储存以色带第i个元素为末尾且满足顺序的所有序列中，序列的最大长度
	dp[0] = 1;
	for (int i = 1; i < dat.size(); i++) {
		int dpmax = 0;
		for (int j = 0; j < i; j++) {
			//元素j的顺序在i之前
			if (map1[dat[i]][dat[j]]) {
				if (dp[j] > dpmax)	dpmax = dp[j];
			}
		}
		dp[i] = (dpmax == 0 ? 1 : dpmax + 1);
	}

	int result = *max_element(dp, dp + dat.size());
	cout << result << endl;
}