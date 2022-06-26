#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;

const int MAX = 1005;
string str;
//dp[i][j]表示字串中第i个与第j个中间的子串是否为回文
bool dp[MAX][MAX] = { 0 };
int result=1;		//最长回文子串的长度

int main(void) {
	ios::sync_with_stdio(false);
	//注意不能直接用cin输入给str，否则得到的是单词而不是一整行
	getline(cin, str);
	int len = str.length();

	//初始化dp矩阵的边界值
	for (int i = 0; i < len; i++) {
		dp[i][i] = true;
		if (str[i] == str[i + 1]) { 
			dp[i][i + 1] = true; 
			result = 2;
		}
	}
	//dp递推
	for (int l = 3; l <= len; l++) {
		for (int i = 0; i <= len - l; i++) {
			int begin = i;
			int end = i + l - 1;
			if (str[begin] == str[end]) {
				if (dp[begin + 1][end - 1]) {
					dp[begin][end] = true;
					result = l;
				}
			}
		}
	}

	cout << result << endl;
}