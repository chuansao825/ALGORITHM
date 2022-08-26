#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;


const int MAX = 105;
//模式字符串
string pattern;
//大小写敏感选项
int sens;
//行数
int n;
//当前输入字符串
string str;
//next数组
int nex[MAX] = { 0 };

//在有敏感判断的条件下判断两字符是否相等
bool equal(char a,char b) {
	//判断敏感开关
	if (sens) {
		return a == b;
	}
	else {
		if (a < 'a')	a += 32;
		if (b < 'a')	b += 32;
		return a == b;
	}
}

//初始化next数组
void init_next() {
	int len = pattern.size();
	nex[0] = -1;
	int j = -1;
	for (int i = 1; i < len; i++) {
		while (j!=-1 && !equal(pattern[i],pattern[j+1])) {
			j = nex[j];
		}
		if (equal(pattern[j+1],pattern[i])) {
			j++;
		}
		nex[i] = j;
	}
}

//判断字符串是否匹配
bool cmp() {
	int j = -1;
	for (int i = 0; i < str.size(); i++) {
		while (j != -1 && !equal(str[i], pattern[j + 1])) {
			j = nex[j];
		}
		if (equal(str[i],pattern[j+1])) {
			j++;
		}
		if (j == pattern.size() - 1)
			return true;
	}
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> pattern;
	cin >> sens >> n;

	//计算pattern的next数组
	init_next();
	for (int i = 0; i < n; i++) {
		cin >> str;
		if (cmp())
			cout << str<<endl;
	}
}