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

string s;
void input() {
	cin >> s;
}


vector<string> result;
unordered_map<int, string> map1;
unordered_map<char, string> map2;
unordered_map<int, string> map3;
void fillmap() {
	map1[0] = "";
	map1[1] = "Shi";
	map1[2] = "Bai";
	map1[3] = "Qian";
	map2['1'] = "yi";
	map2['2'] = "er";
	map2['3'] = "san";
	map2['4'] = "si";
	map2['5'] = "wu";
	map2['6'] = "liu";
	map2['7'] = "qi";
	map2['8'] = "ba";
	map2['9'] = "jiu";
	map3[2] = "Yi";
	map3[1] = "Wan";
	map3[0] = "";
}


struct node {
	string data;
	string bit;
	char d;
	int b;
	node(char _d, int _b) :d(_d), b(_b) {}
};


vector<struct node> vec;
void solve() {
	if (s[0] == '-') {
		result.push_back("Fu");
		s.erase(s.begin());
	}
	
	//将开头的0去掉
	while (!s.empty()) {
		if (s.front() == '0')
			s.erase(s.begin());
		else
			break;
	}
	//若为全0则返回
	if (s.empty()) {
		result.clear();
		result.push_back("ling");
		return;
	}

	int b = 0;
	while (!s.empty()) {
		char ch = s.back();
		s.pop_back();
		vec.insert(vec.begin(),node(ch,b%4));
		b++;
	}
	
	for (int i = 0; i < vec.size(); i++) {
		struct node& n = vec[i];
		if (n.d != '0') {
			if (i >= 1&&vec[i - 1].d == '0')
				result.push_back("ling");
			result.push_back(map2[n.d]);
			result.push_back(map1[n.b]);
		}			
		if ((vec.size()-i-1)%4==0) {
			result.push_back(map3[(vec.size() - i-1) / 4]);
		}
	}
}


int main(void) {
	input();
	fillmap();
	solve();
	vector<string> v;
	for (int i = 0; i < result.size(); i++) {
		if (!result[i].empty())
			v.push_back(result[i]);
	}
	result.swap(v);

	for (int i = 0; i < result.size(); i++) {
		cout << result[i];
		if (i == result.size() - 1)
			cout << endl;
		else
			cout << " ";
	}
}


/*
-123456789

100800


1050500

000

*/