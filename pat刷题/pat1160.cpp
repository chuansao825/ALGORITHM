#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<set>
#include<cmath>
using namespace std;

#define ll long long

struct node {
	int K;
	int m;
	node(int a,int b):K(a),m(b){}
	node(){}
};
int N;
const int MAX = 5;
struct node args[MAX];
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int K, m;
		cin >> K >> m;
		args[i] = node(K, m);
	}
}


//��λ֮��
int dsum(ll x) {
	int sum = 0;
	while (x>0) {
		sum += x % 10;
		x = x / 10;
	}
	return sum;
}



//�ж�����
bool isprime(ll x) {
	int sqr = sqrt(x);
	for (ll i = 2; i <= sqr; i++) {
		if (x % i == 0)
			return false;
	}
	return true;
}

//�����Լ��
ll gcd(ll x,ll y) {
	if (y==0) {
		return x;
	}
	return gcd(y, x % y);
}

set<pair<int, ll>> result;
void solve(int K,int m) {
	//��ֵ�Ͻ�
	ll ub = 0;
	for (int i = 0; i < K; i++) {
		ub = 10 * ub + 9;
	}
	//������֪���ܵ�ȡֵĩβ��Ϊ9������Ҫ��֦
	ll lb = pow(10,K-1)+9;
	for (ll i = lb; i < ub; i+=10) {
		if (dsum(i) == m) {
			int n = dsum(i + 1);
			//�����Լ��
			ll mygcd = gcd(m, n);
			if (mygcd <= 2)
				continue;
			//�ж��Ƿ�Ϊ����
			if (isprime(mygcd)) {
				result.insert(make_pair(n, i));
			}
		}
		else
			continue;
	}
}





int main(void) {
	input();

	for (int i = 0; i < N; i++) {
		int K = args[i].K;
		int m = args[i].m;
		solve(K, m);
		//���
		cout << "Case " << i + 1 << endl;
		if (!result.empty())
			for (auto it = result.begin(); it != result.end(); it++) {
				cout << it->first << " " << it->second << endl;
			}
		else
			cout << "No Solution" << endl;
		//����result
		result.clear();
	}

	return 0;
}


/*
2
6 45
7 80

*/