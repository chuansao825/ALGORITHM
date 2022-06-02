#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long

//用于优先队列
struct node {
	ll w;		//权值
	int depth;	//深度
	node(ll _w,int _d):w(_w),depth(_d){}
};

//用于结点间比较
struct cmp {
	bool operator()(const struct node& a, const struct node& b) {
		if (a.w != b.w)		return a.w > b.w;
		return a.depth > b.depth;
	}
};

//优先队列
priority_queue<struct node, vector<struct node>, cmp> pq;

int main(void) {
	//n种单词，k进制str
	int n, k;	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		ll w;	cin >> w;	pq.push(node(w,0));
	}	

	//对于多叉树，加入虚的叶子结点(坑)
	while ((n - 1) % (k - 1)) {
		n++;
		pq.push(node(0, 0));
	}

	//ans：总的最短长度	minlen：最长字串的最短长度
	ll ans=0,minlen=0;	
	while (pq.size()>1) {
		//储存k个元素中depth的最大值
		int maxdepth = 0;
		ll tempw=0;
		//pop出k个元素
		for (int i = 0; i < k; i++) {
			//对于剩余元素不到k个特殊处理
			if (pq.size() == 0)	break;
			tempw += pq.top().w;
			if (maxdepth < pq.top().depth)		maxdepth = pq.top().depth;
			pq.pop();
		}
		maxdepth++;
		//更新ans和minlen
		ans += tempw;
		if(minlen<maxdepth)		minlen = maxdepth;
		//加入新的结点
		pq.push(node(tempw, maxdepth));
	}

	cout << ans << endl << minlen << endl;
}