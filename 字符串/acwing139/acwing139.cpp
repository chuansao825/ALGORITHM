#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
#pragma GCC optimize(2)
using namespace std;

typedef long long ll;
const int MAXLEN = 1000005;
const int MAXNUM = 35;
int strnum=0;		//字符串的数量
//正序和逆序的字符串
string s1, s2;
//结果
int result[MAXNUM] = { 0 };
//进制数
ll p = 10000019;
//mod
ll mod = 1000000007;
//H数组，H[i]表示字符串前i个字符的子串的hash值
ll H1[MAXLEN] = { 0 }, H2[MAXLEN] = { 0 };
//powp[i]表示p的i次方
ll powp[MAXLEN] = { 0 };

//计算字符串的H数组
void calH(ll* H,string& str) {
	H[0] = str[0];
	for (int i = 1; i < str.size(); i++) {
		H[i] = (H[i - 1] * p + str[i]) % mod;
	}
}

//打表,预先求出p的幂次
void getpowp() {
	powp[0] = 1;
	for (int i = 1; i < MAXLEN; i++) {
		powp[i] = (powp[i - 1] * p)%mod;
	}
}

//计算子串的哈希值
ll calsubH(ll* H,int i,int j){
	//对i为0的情况特殊处理
	if (i == 0)
		return H[j];
	else
		return ((H[j] - H[i - 1] * powp[j - i + 1]) % mod + mod) % mod;
}

//比较两个子串是否相等
bool cmp(int i1,int j1,int i2,int j2) {
	return calsubH(H1, i1, j1) == calsubH(H2, i2, j2);	
}

//对字符串进行预处理，每两个字符之间插入一个'#'
void initstring(string& tmp,int& len) {
	len = 2 * len - 1;
	char* ch = new char[len + 1];
	for (int i = 0; i < len; i++) {
		if (i % 2 == 0)	ch[i] = tmp[i / 2];
		else    ch[i] = '#';
	}
	ch[len] = '\0';
	tmp = string(ch);
}

//计算以第i个字符为中心时，回文子串的最大长度
//字符串s1，字符串s2为其反序
int calbyi(int i,int len) {
	//搜索区间的最小值、最大值
	int lb = 0, rb = min(i, len - i-1);	
	//字串的半径(不包括中心点)，注意必须初始化应对i=0的情况
	int k=0;
	
	//使用二分法求解
	while (rb > lb) {
		//注意半径要大于等于1,否则会在第一个分支中死循环
		k = (lb + rb) / 2+1;
		//正、反序字串中要比较的子串的开始位置
		int b1 = i - k, b2 = len - k - (i + 1);
		//判断子串哈希值是否相等
		if (cmp(b1,b1+k-1,b2,b2+k-1)) {
			//以i为中心，k为半径的子串是回文子串，可以向两边拓展(用二分的方法)
			//所以修改区间的最小值，表示半径最少有k个字符
			lb = k;
		}
		else {
			//以i为中心，k为半径的子串不是回文子串，所以向中心收缩半径
			//修改区间的最大值，表示半径要小于k个字符
			rb = k - 1;
		}		
	}

	//求除掉'#'后的回文子串的长度,注意这里半径不能用k，因为上面退出循环时可能k的值大于正确半径
	//要根据中心字符的类型来判断
	//中心为'#'，回文子串为偶数长度
	if (s1[i] == '#') {
		return ((lb + 1) / 2) * 2;
	}
	//中心为英文字符，回文串为奇数长度
	else{
		return 2*(lb/2) + 1;
	}
}

//计算字符串s1的最长回文字串长度
int cal(int len) {
	int maxlen=1;	//回文串的最大长度
	//遍历所有点，将其作为中心点求解
	for (int i = 0; i < len; i++) {
		maxlen = max(calbyi(i,len), maxlen);
	}
	return maxlen;
}


int main(void) {
	ios::sync_with_stdio(false);
	getpowp();		//打表

	//给s1,s2预留空间来优化
	s1.reserve(MAXLEN);
	s2.reserve(MAXLEN);

	//对所有字符串求解其最长回文子串长度
	string inputstr;
	int strnum = 0;
	int len = 0;
	while(true) {
		getline(cin, s1);
		if (s1 == "END")		break;
		//原始字符串和反序字符串
		len = s1.size();
		initstring(s1,len);		//给字符之间插入'#'
		s2 = s1;
		reverse(s2.begin(), s2.end());
		//计算两个字符串的H数组
		calH(H1, s1);
		calH(H2, s2);
		//求解
		result[++strnum]=cal(len);
	}
	
	//输出结果
	for (int i = 1; i <= strnum; i++) {
		cout << "Case " << i << ": " << result[i] << endl;
	}
}