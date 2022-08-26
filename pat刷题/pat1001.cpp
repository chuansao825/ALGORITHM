#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<stack>
using namespace std;

int a, b;
int c;

int main(void) {
	cin >> a >> b;
	c = a + b;
	string s = to_string(c);
	if (c >= 0)		s.insert(s.begin(), '+');
	stack<char> mystack;
	int count = 0;
	for (int i = s.size()-1; i > 0; i--,count++) {
		char ch = s[i];
		if (count % 3 == 0 && count != 0) {
			mystack.push(',');
		}
		mystack.push(ch);
	}

	string str = "";
	while (!mystack.empty()) {
		char ch = mystack.top();
		mystack.pop();
		str.push_back(ch);
	}
	
	if (c < 0)
		str.insert(str.begin(), '-');

	cout << str << endl;

	return 0;
}


/*
-1000000 9

-80000 100000

*/