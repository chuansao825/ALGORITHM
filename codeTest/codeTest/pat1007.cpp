#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAX = 10010;
int K = 0;
struct node {
	int start, end, v;
	node(int a,int b,int c):start(a),end(b),v(c){}
	node(){}
};
//dp数组,第i个元素储存以i为末尾的序列的最大值
struct node dp[MAX];
//原始data
int dat[MAX] = { 0 };
//全为负数？
bool flag = true;
void input() {
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> dat[i];
		if (dat[i] >= 0)	flag = false;
	}
}

struct cmp {
	bool operator()(const struct node& a, const struct node& b) {
		if (a.v != b.v)	return a.v > b.v;
		if (a.start != b.start)	return a.start < b.start;
		if (a.end != b.end)	return a.end < b.end;
	}
};

int main(void) {
	ios::sync_with_stdio(false);
	input();
	if (flag) {
		cout << 0 << " " << dat[0] << " " << dat[K - 1] << endl;
		return 0;
	}
	
	//dp计算
	dp[0] = node(0, 0, dat[0]);
	for (int i = 1; i < K; i++) {
		int s, v;
		if (dp[i - 1].v >= 0) {
			s = dp[i - 1].start;
			v = dp[i - 1].v + dat[i];			
		}
		else {
			s = i;
			v = dat[i];
		}
		dp[i] = node(s, i, v);
	}

	//输出结果
	//将结果排序
	sort(dp, dp + K, cmp());
	cout << dp[0].v <<" "<< dat[dp[0].start] <<" "<< dat[dp[0].end]<<endl;
}