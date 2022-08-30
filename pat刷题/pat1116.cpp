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

int N, K;
//key：ID	value：排名,from 1
unordered_map<string, int> rk;	
vector<string> ql;	//查询列表
set<string> visit;	//标记已被查询的元素
void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		string str;
		cin >> str;
		rk[str] = i;
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		string str;
		cin>>str;
		ql.push_back(str);
	}
}


bool isPrime(int num) {
	int sqr = sqrt(num);
	for (int i = 2; i <= sqr; i++) {
		if (num % i == 0)
			return false;
	}
	return true;
}

int main(void) {
	input();
	
	for (int i = 0; i < K; i++) {
		string id = ql[i];
		cout << id << ": ";
		if(visit.find(id)!=visit.end()){
			cout<<"Checked" << endl;
			continue;
		}
		if (rk.find(id) == rk.end()) {
			cout << "Are you kidding?" << endl;
			continue;
		}
		if (rk[id] == 1) {
			cout << "Mystery Award" << endl;
		}
		else if (isPrime(rk[id])) {
			cout << "Minion" << endl;
		}
		else {
			cout << "Chocolate" << endl;
		}

		visit.insert(id);
	}
	
}


/*
6
1111
6666
8888
1234
5555
0001
6
8888
0001
1111
2222
8888
2222

*/