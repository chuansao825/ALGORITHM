#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;

const int MAX = 1005;
string str;
//dp[i][j]��ʾ�ִ��е�i�����j���м���Ӵ��Ƿ�Ϊ����
bool dp[MAX][MAX] = { 0 };
int result=1;		//������Ӵ��ĳ���

int main(void) {
	ios::sync_with_stdio(false);
	//ע�ⲻ��ֱ����cin�����str������õ����ǵ��ʶ�����һ����
	getline(cin, str);
	int len = str.length();

	//��ʼ��dp����ı߽�ֵ
	for (int i = 0; i < len; i++) {
		dp[i][i] = true;
		if (str[i] == str[i + 1]) { 
			dp[i][i + 1] = true; 
			result = 2;
		}
	}
	//dp����
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