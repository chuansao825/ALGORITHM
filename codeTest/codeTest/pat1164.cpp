#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAX1 = 200;
const int MAX2 = 10;

//存原始矩阵
char m[MAX1][MAX2] = { 0 };
//存句子
string sentence = "";
vector<string> words;

void input() {
	char ch;
	for (int i = 1; i <= 26 * 7; i++) {
		for (int j = 1; j <= 5; j++) {
			cin >> m[i][j];
		}
		char t=getchar();
		ch = t;
	}
	
	//要注意空格
	getline(cin, sentence);
}

//将句子分为各个单词
void split() {	
	string str = "";
	bool pre = false;	//前一个字符为大写字母?
	for (int i = 0; i < sentence.size(); i++) {
		char ch = sentence[i];
		if (ch >= 'A' && ch <= 'Z') {
			str += ch;
			pre = true;
			//特殊情况
			if (i == sentence.size() - 1) {
				words.push_back(str);
			}
		}
		else {
			if (pre) {
				words.push_back(str);
				str = "";
				pre = false;
			}
		}
	}
}

//order:字母的顺序
void mycopy(char ch,char** mat,int order) {
	//复制的基准点
	int x1 = (ch - 65) * 7 + 1;
	int y1 = 1;
	int x2 = 1;
	int y2 = order * 6 + 1;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 5; j++) {
			mat[i+x2][y2 + j] = m[x1+i][y1+j];
		}
		//处理空格
		mat[i + x2][y2 + 5] = ' ';
	}
}


int main(void) {
	input();
	split();

	int wordnum = words.size();
	//创建一个矩阵储存该单词
	char** mat = new char* [10];
	for (int i = 0; i < 10; i++) {
		mat[i] = new char[100];
	}
	for (int k = 0; k < wordnum; k++) {
		string word = words[k];
		int len = word.size();
		//遍历每个字母加入矩阵中
		for (int i = 0; i < word.size(); i++) {
			char ch = word[i];
			mycopy(ch, mat, i);
		}
		//输出矩阵
		for (int i = 1; i <= 7; i++) {
			for (int j = 1; j <= 6 * word.size() - 1; j++) {
				/*printf("%c",mat[i][j])*/;
				cout << mat[i][j];
			}
			if (wordnum - 1 == k && i == 7)
				continue;
			else if (i < 7)
				cout << endl;
			else if (i == 7 && wordnum - 1 != k)
				cout << endl << endl;
		}
	}
	
	return 0;
}


/*
..C..
.C.C.
C...C
CCCCC
C...C
C...C
C...C
CCCC.
C...C
C...C
CCCC.
C...C
C...C
CCCC.
.CCC.
C...C
C....
C....
C....
C...C
.CCC.
CCCC.
C...C
C...C
C...C
C...C
C...C
CCCC.
CCCCC
C....
C....
CCCC.
C....
C....
CCCCC
CCCCC
C....
C....
CCCC.
C....
C....
C....
CCCC.
C...C
C....
C.CCC
C...C
C...C
CCCC.
C...C
C...C
C...C
CCCCC
C...C
C...C
C...C
CCCCC
..C..
..C..
..C..
..C..
..C..
CCCCC
CCCCC
....C
....C
....C
....C
C...C
.CCC.
C...C
C..C.
C.C..
CC...
C.C..
C..C.
C...C
C....
C....
C....
C....
C....
C....
CCCCC
C...C
C...C
CC.CC
C.C.C
C...C
C...C
C...C
C...C
C...C
CC..C
C.C.C
C..CC
C...C
C...C
.CCC.
C...C
C...C
C...C
C...C
C...C
.CCC.
CCCC.
C...C
C...C
CCCC.
C....
C....
C....
.CCC.
C...C
C...C
C...C
C.C.C
C..CC
.CCC.
CCCC.
C...C
CCCC.
CC...
C.C..
C..C.
C...C
.CCC.
C...C
C....
.CCC.
....C
C...C
.CCC.
CCCCC
..C..
..C..
..C..
..C..
..C..
..C..
C...C
C...C
C...C
C...C
C...C
C...C
.CCC.
C...C
C...C
C...C
C...C
C...C
.C.C.
..C..
C...C
C...C
C...C
C.C.C
CC.CC
C...C
C...C
C...C
C...C
.C.C.
..C..
.C.C.
C...C
C...C
C...C
C...C
.C.C.
..C..
..C..
..C..
..C..
CCCCC
....C
...C.
..C..
.C...
C....
CCCCC
~HELLO~WORLD!

*/


