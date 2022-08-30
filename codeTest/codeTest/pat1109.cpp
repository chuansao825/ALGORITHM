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
struct node {
	string name;
	int h;
	node() {}
	node(string a,int b):name(a),h(b){}
};
vector<struct node> people;
void input() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		string str; int h;
		cin >> str >> h;
		people.push_back(node(str, h));
	}
}


vector<int> rc;	//ÿ����������0��ʼ
void getRC() {
	//�ж�ÿ������
	int tmp = 0;
	for (int i = 0; i < K - 1; i++) {
		rc.push_back(N / K);
		tmp += N / K;
	}
	rc.push_back(N - tmp);	//���һ��
}

struct cmp {
	bool operator()(const struct node& a, const struct node& b) {
		if (a.h != b.h)
			return a.h > b.h;
		return a.name < b.name;
	}
};

//����
vector<vector<struct node>> plan;
int main(void) {
	input();
	getRC();
	
	sort(people.begin(), people.end(), cmp());
	//���շ������ַ�������
	int idx = 0;	//people����ָ��
	for (int i = K-1; i>=0; i--) {
		int n = rc[i];	//��������
		vector<struct node> v;
		v.reserve(n);
		int mid = n / 2;
		//v[mid] = people[idx++];
		v.push_back(people[idx++]);
		//������ҷַ�
		for(int i=0;i<n-1;i++) {
			struct node n = people[idx++];
			if (i % 2 == 0) {
				v.insert(v.begin(), n);
			}
			else {
				v.push_back(n);
			}
		}
		//д��
		plan.push_back(v);
	}

	//output
	for (int i = 0; i < plan.size(); i++) {
		vector<struct node> v = plan[i];
		for (int j = 0; j < v.size(); j++) {
			if (j == v.size() - 1)
				cout << v[j].name;
			else
				cout << v[j].name << " ";
		}
		if (i != plan.size() - 1)
			cout << endl;
	}
}



/*
10 3
Tom 188
Mike 170
Eva 168
Tim 160
Joe 190
Ann 168
Bob 175
Nick 186
Amy 160
John 159

*/