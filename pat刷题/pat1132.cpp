#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
#include<unordered_map>
#include<queue>
#include<stack>
using namespace std;


int N;
vector<string> s;
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		s.push_back(str);
	}
}

bool judge(string str) {
	int len = str.size()/2;
	//cut
	string str1 = str.substr(0, len);
	string str2=str.substr(len, len);
	int num = stoi(str);
	int x = stoi(str1);
	int y = stoi(str2);
	if ((x * y) != 0&&num % (x * y) == 0) {
		return true;
	}
	else
		return false;
}

int main(void) {
	input();
	for (int i = 0; i < N; i++) {
		if (judge(s[i]))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	}
}


/*
4
167334
2333
12345678
2000
*/
