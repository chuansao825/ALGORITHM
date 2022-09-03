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

int D, N;
void input() {
	cin >> D >> N;
}

struct node {
	char ch;
	int count;
	node(char c) { ch = c; count = 1; }
};

string str="";
vector<struct node> vec;
void solve() {
	str = to_string(D);
	//进行N-1轮迭代
	for (int i = 0; i < N - 1; i++) {
		//遍历一次子串
		string s = "";
		for (int j = 0; j < str.size(); j++) {
			char ch = str[j];
			if (vec.empty()) {
				vec.push_back(node(ch));
			}
			else {
				if (ch == vec[vec.size() - 1].ch) {
					vec[vec.size() - 1].count++;
				}
				else
					vec.push_back(node(ch));
			}			
		}

		for (int k = 0; k < vec.size(); k++) {
			char ch = vec[k].ch;
			int count = vec[k].count;
			s.push_back(ch);
			s+=to_string(count);
		}
		str = s;
		vec.clear();
	}
}

int main(void) {
	input();
	solve();
	cout << str << endl;
}


/*
1 8

*/