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

struct edge {
	int v;
	int w;
	edge(int _v,int _w):v(_v),w(_w){}
};
const int MAX = 2005;
vector<struct edge> adj[MAX];
unordered_map<string, int> map1;
unordered_map<int, string> map2;

int N, K;
void input() {
	cin >> N >> K;
	int id = 0;
	for (int i = 0; i < N; i++) {
		string s1, s2; int w;
		cin >> s1 >> s2 >> w;
		int id1, id2;
		if (map1.find(s1) == map1.end()) {
			map1[s1] = id;
			map2[id] = s1;
			id++;
		}
		if (map1.find(s2) == map1.end()) {
			map1[s2] = id;
			map2[id] = s2;
			id++;
		}
		id1 = map1.find(s1)->second;
		id2 = map1.find(s2)->second;
		int j;
		for (j = 0; j < adj[id1].size(); j++) {
			if (adj[id1][j].v == id2) {
				adj[id1][j].w += w;
				break;
			}
		}
		if (j == adj[id1].size()) {
			adj[id1].push_back(edge(id2, w));
		}
		for (j = 0; j < adj[id2].size(); j++) {
			if (adj[id2][j].v == id1) {
				adj[id2][j].w += w;
				break;
			}
		}
		if (j == adj[id2].size()) {
			adj[id2].push_back(edge(id1, w));
		}
	}
}

struct gang {
	string head;
	int num;
	gang(string a,int b):head(a),num(b){}
};

vector<struct gang> result;
bool visit[MAX] = { false };

void BFS(int id) {
	queue<int> q;
	vector<int> vec;
	q.push(id);
	int totalw = 0;
	visit[id] = true;
	while (!q.empty()) {
		int u = q.front();
		vec.push_back(u);
		q.pop();
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].v;
			if (visit[v])
				continue;
			visit[v] = true;
			q.push(v);
		}		
	}

	if (vec.size() > 2) {
		unordered_map<int, int> m;
		//¼ÆËã×Ü±ßÈ¨
		for (int i = 0; i < vec.size(); i++) {
			int u = vec[i];
			int x = 0;
			for (int j = 0; j < adj[u].size(); j++) {
				x += adj[u][j].w;
			}
			totalw += x;
			m[u] = x;
		}
		totalw /= 2;
		if (totalw > K) {
			int num = vec.size();
			int head = 0;
			int max = 0;
			for (auto it = m.begin(); it != m.end(); it++) {
				if (it->second > max) {
					max = it->second;
					head = it->first;
				}
			}
			result.push_back(gang(map2[head], vec.size()));
		}
	}
}

struct cmp {
	bool operator()(const struct gang& a, const struct gang& b) {
		return a.head < b.head;
	}
};

void findgang() {
	for (auto it = map2.begin(); it != map2.end(); it++) {
		int id = it->first;
		BFS(id);
	}
	sort(result.begin(), result.end(), cmp());
}


int main(void) {
	ios::sync_with_stdio(false);
	input();
	findgang();
	cout << result.size() << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i].head << " " << result[i].num << endl;
	}
}


/*
8 59
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10

4 3
A B 1
A C 1
C A 1
B C 3

8 70
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10


*/