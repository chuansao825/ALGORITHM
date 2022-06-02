#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long

//�������ȶ���
struct node {
	ll w;		//Ȩֵ
	int depth;	//���
	node(ll _w,int _d):w(_w),depth(_d){}
};

//���ڽ���Ƚ�
struct cmp {
	bool operator()(const struct node& a, const struct node& b) {
		if (a.w != b.w)		return a.w > b.w;
		return a.depth > b.depth;
	}
};

//���ȶ���
priority_queue<struct node, vector<struct node>, cmp> pq;

int main(void) {
	//n�ֵ��ʣ�k����str
	int n, k;	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		ll w;	cin >> w;	pq.push(node(w,0));
	}	

	//���ڶ�������������Ҷ�ӽ��(��)
	while ((n - 1) % (k - 1)) {
		n++;
		pq.push(node(0, 0));
	}

	//ans���ܵ���̳���	minlen����ִ�����̳���
	ll ans=0,minlen=0;	
	while (pq.size()>1) {
		//����k��Ԫ����depth�����ֵ
		int maxdepth = 0;
		ll tempw=0;
		//pop��k��Ԫ��
		for (int i = 0; i < k; i++) {
			//����ʣ��Ԫ�ز���k�����⴦��
			if (pq.size() == 0)	break;
			tempw += pq.top().w;
			if (maxdepth < pq.top().depth)		maxdepth = pq.top().depth;
			pq.pop();
		}
		maxdepth++;
		//����ans��minlen
		ans += tempw;
		if(minlen<maxdepth)		minlen = maxdepth;
		//�����µĽ��
		pq.push(node(tempw, maxdepth));
	}

	cout << ans << endl << minlen << endl;
}