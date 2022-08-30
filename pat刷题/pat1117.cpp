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
using namespace std;

//E:至少有E个输入的值严格大于E

const int MAX = 100005;
int N;
set<int> num;	//出现过的数字
unordered_map<int, int> times;		//储存每个数字出现的次数(不能用数组，data的值可能会越界)
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		times[x]++;
		num.insert(x);
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	input();
	auto it = max_element(num.begin(), num.end());
	int m = *it;
	int cum = 0;
	int answer=0;
	for (int i = m; i >= 0; i--) {
		if (cum >= i) {
			answer = i;
			break;
		}
		if (times.find(i) != times.end()) {
			cum += times[i];
		}
		
	}

	cout << answer << endl;
}

/*
10
6 7 6 9 3 10 8 2 7 8

1
0

2
2 3

5
5 5 5 5 5

5
0 0 0 0 0

*/