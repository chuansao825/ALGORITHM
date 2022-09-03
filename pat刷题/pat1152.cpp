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
#define ll long long

int L, K;
string s;
void input() {
	cin >> L >> K;
	cin >> s;
}


bool isprime(string str) {
	ll x = stoll(str);
	str = to_string(x);
	int len = str.length();
	if (len == 0)
		return false;
	else if (len==1) {
		if (x == 0 || x == 1 || x == 4 || x == 6 || x == 8 || x == 9)
			return false;
		else
			return true;
	}
	else {
		int y = str[len - 1]-48;
		if (y == 4 || y == 6 || y == 8)
			return false;
		else {
			ll sqr = sqrt(x);
			for (int i = 2; i <= sqr; i++) {
				if (x % i == 0)
					return false;
			}
			return true;
		}
	}

}

string result="";
void solve() {
	for (int i = 0; i <= L - K; i++) {
		if (isprime(s.substr(i, K))) {
			result = s.substr(i, K);
			break;
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	input();
	solve();

	if (result.empty())
		cout << "404" << endl;
	else
		cout << result << endl;


}


/*
20 5
23654987725541023819


10 3
2468024680


1000 10
2718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427466391932003059921

*/