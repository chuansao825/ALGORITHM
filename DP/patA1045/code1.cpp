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
//newl����ȥ�����в�ϲ������ɫ���ɫ��Ԫ�ظ���
int newl;
//keyΪһ��ϲ������ɫ��valueΪ˳����key֮ǰ��������ɫ
bool map1[MAX2][MAX2] = { false };
//����ȥ����ϲ����ɫ���ɫ��
vector<int> dat;
//����ϲ������ɫ
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

//����ӳ��
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

	//dp���,dp[i]������ɫ����i��Ԫ��Ϊĩβ������˳������������У����е���󳤶�
	dp[0] = 1;
	for (int i = 1; i < dat.size(); i++) {
		int dpmax = 0;
		for (int j = 0; j < i; j++) {
			//Ԫ��j��˳����i֮ǰ
			if (map1[dat[i]][dat[j]]) {
				if (dp[j] > dpmax)	dpmax = dp[j];
			}
		}
		dp[i] = (dpmax == 0 ? 1 : dpmax + 1);
	}

	int result = *max_element(dp, dp + dat.size());
	cout << result << endl;
}