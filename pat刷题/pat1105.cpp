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



int N;
vector<int> dat;
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		dat.push_back(tmp);
	}
}

struct cmp {
	bool operator()(const int& a,const int& b){
		return a > b;
	}
};



int m, n;
void getMN() {
	int sqr = sqrt(N);
	for (int i = sqr; i >= 1; i--) {
		if (N % i == 0) {
			n = i;
			m = N / n;
			break;
		}
	}
}

vector<vector<int>> mat;
void initMat() {
	for (int i = 0; i < m; i++) {
		vector<int> v;
		for (int j = 0; j < n; j++) {
			v.push_back(0);
		}
		mat.push_back(v);
	}
}

void solve() {
	int i=0, j=0;	//当前位置
	//矩阵上下界
	int ilb = 0, iub = m - 1;
	int jlb = 0, jub = n - 1;
	//上一个点的位置
	int prex=0, prey=-1;

	for (int k = 0; k < N; k++) {
		mat[i][j] = dat[k];
		//确定下一个点位置
		int deltax = i - prex, deltay = j - prey;
		//更新prex prey
		prex = i, prey = j;
		if (deltax == 0 && deltay == 1) {
			//判断边界
			if (j == jub) {
				//到了边界，改变边界
				ilb++;
				i++;
			}
			else {
				j++;
			}
		}
		else if (deltax == 1 && deltay == 0) {
			if (i == iub) {
				jub--;
				j--;
			}
			else {
				i++;
			}
		}
		else if (deltax == 0 && deltay == -1) {
			if (j == jlb) {
				iub--;
				i--;
			}
			else {
				j--;
			}
		}
		else if (deltax == -1 && deltay == 0) {
			if (i == ilb) {
				jlb++;
				j++;
			}
			else {
				i--;
			}
		}

		
	}
}

int main(void) {
	input();
	//将原始数据降序排序
	sort(dat.begin(), dat.end(), cmp());
	//确定m,n
	getMN();
	//创建矩阵
	initMat();
	solve();

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << mat[i][j];
			if (j != n - 1)
				cout << " ";
			else
				cout << endl;
		}
	}
}


/*
12
37 76 20 98 76 42 53 95 60 81 58 93

4
2 3 1 4

1
10

2
3 5

5
1 2 3 4 5

6
2 3 1 4 5 6

9
1 2 3 4 5 6 7 8 9

16
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16

13
1 2 3 4 5 6 7 8 9 10 11 12 13

25
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

*/