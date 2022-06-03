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
//����ȥ����ϲ����ɫ���ɫ��
vector<int> dat;
//ӳ�䣬��ϲ������ɫӳ�䵽0,1,2...
int myhash[MAX2];

void input() {
	cin >> N;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int c; cin >> c;
		myhash[c] = i;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int c; cin >> c;
		if (myhash[c]!=-1) {
			dat.push_back(c);
		}
	}
}

int dp[MAX] = { 0 };
int main(void) {
	fill(myhash, myhash + MAX2, -1);
	ios::sync_with_stdio(false);
	input();

	//dp���,dp[i]������ɫ����i��Ԫ��Ϊĩβ������˳������������У����е���󳤶�
	dp[0] = 1;
	for (int i = 1; i < dat.size(); i++) {
		int dpmax = 0;
		for (int j = 0; j < i; j++) {
			//Ԫ��j��˳����i֮ǰ
			if (myhash[dat[i]]>=myhash[dat[j]]) {
				if (dp[j] > dpmax)	dpmax = dp[j];
			}
		}
		dp[i] = (dpmax == 0 ? 1 : dpmax+1);
	}

	int result=*max_element(dp,dp+dat.size());
	cout << result << endl;
}