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

struct node {
	char level;
	string site;
	string date;
	string id;
	string card;
	int score;
	node(char a,string b,string c,string d,string e,int f){
		level = a;
		site = b;
		date = c;
		id = d;
		card = e;
		score = f;
	}
};

struct node toNode(string card,int score) {
	string s = card;
	s.insert(s.begin(), '0');
	char level = s[1];
	string site = s.substr(2, 3);
	string date = s.substr(5, 6);
	string id = s.substr(11, 3);
	return node(level, site, date, id, card, score);
}

struct node3 {
	int type;
	string s;
	node3(int a, string b) :type(a), s(b){}
	node3(){}
	string toString() { return to_string(type) + " "+s; }
};

const int MAX = 105;
int N, M;
vector<struct node> dat;
struct node3 query[MAX];
void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		string str;
		int score;
		cin >> str>>score;
		dat.push_back(toNode(str, score));
	}
	for (int i = 1; i <= M; i++) {
		int type;
		string s;
		cin >> type >> s;
		query[i]=node3(type,s);
	}
}

struct node2 {
	string site;
	int sitenum;
	node2(string a,int b):site(a),sitenum(b){}
};

//提前打表,将数据按照不同的key分类并排序，然后储存
unordered_map<char, vector<struct node>> map1;	//key:level
unordered_map<string, pair<int, int>> map2;		//value:the total number of testees together with their total scores in a given site
unordered_map<string, vector<struct node>> map3;		//key:date
void getMAP() {
	for (int i = 0; i < N; i++) {
		struct node n = dat[i];
		map1[n.level].push_back(n);

		if (map2.find(n.site)==map2.end()) {
			map2.insert(make_pair(n.site,make_pair(1, n.score)));
		}
		else {
			map2[n.site].first++;
			map2[n.site].second += n.score;
		}

		map3[n.date].push_back(n);
	}
}

struct cmp1 {
	bool operator()(const struct node& a, const struct node& b) {
		if (a.score != b.score)
			return a.score > b.score;
		else
			return a.card < b.card;
	}
};
struct cmp3 {
	bool operator()(const struct node2& a, const struct node2& b) {
		if (a.sitenum != b.sitenum) {
			return a.sitenum > b.sitenum;			
		}
		return a.site < b.site;
	}
};

unordered_map<string, bool> map4;
unordered_map<string, vector<struct node2>>map5;


int main(void) {
	ios::sync_with_stdio(false);
	input();
	getMAP();
	//sortMAP();

	//处理查询
	for (int i = 1; i <= M; i++) {
		struct node3 q = query[i];
		cout << "Case " << i << ": " << q.toString() << endl;
		if (q.type == 1) {			
			if (map1.find(q.s[0])!=map1.end()) {
				vector<struct node> vec;
				if (map4[q.s]) {
					vec = map1[q.s[0]];
				}
				else {
					vector<struct node>& v = map1[q.s[0]];
					sort(v.begin(), v.end(), cmp1());
					map4[q.s] = true;
					vec = v;
				}
				for (int i = 0; i < vec.size(); i++) {
					cout << vec[i].card << " " << vec[i].score << endl;
				}
			}
			else {
				cout << "NA" << endl;
			}
		}
		else if (q.type == 2) {
			if (map2.find(q.s) != map2.end()) {
				pair<int, int> p = map2[q.s];
				cout << p.first << " " << p.second<<endl;
			}
			else {
				cout << "NA" << endl;
			}
			
		}
		else if (q.type == 3) {
			if (map3.find(q.s) != map3.end()) {
				vector<struct node2> vec;
				if (map5.find(q.s)!=map5.end()) {
					vec = map5[q.s];
				}
				else {
					vector<struct node2> v;
					unordered_map<string, int> m;	//考点-人数
					for (int i = 0; i < map3[q.s].size(); i++) {
						struct node& n = map3[q.s][i];
						if (m.find(n.site) == m.end()) {
							m[n.site] = 1;
						}
						else {
							m[n.site]++;
						}
					}
					for (auto it = m.begin(); it != m.end(); it++) {
						v.push_back(node2(it->first, it->second));
					}					
					sort(v.begin(), v.end(), cmp3());
					map5[q.s] = v;
					vec = v;
				}
				for (int i = 0; i < vec.size(); i++) {
					cout << vec[i].site << " " << vec[i].sitenum << endl;
				}
			}
			else {
				cout << "NA" << endl;
			}
		}
	}
}


/*
8 4
B123180908127 99
B102180908003 86
A112180318002 98
T107150310127 62
A107180908108 100
T123180908010 78
B112160918035 88
A107180908021 98
1 A
2 107
3 180908
2 999

8 1
B123180908127 99
B102180908003 86
A112180318002 98
T107150310127 62
A107180908108 100
T123180908010 78
B112160918035 88
A107180908021 98
1 A

8 2
B123180908127 99
B102180908003 86
A112180318002 98
T107150310127 62
A107180908108 100
T123180908010 78
B112160918035 88
A107180908021 98
3 180908
3 180908

*/