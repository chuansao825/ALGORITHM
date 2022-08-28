#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAX1 = 200;
const int MAX2 = 10;

//��ԭʼ����
char m[MAX1][MAX2] = { 0 };
//�����
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
	
	//Ҫע��ո�
	getline(cin, sentence);
}

//�����ӷ�Ϊ��������
void split() {	
	string str = "";
	bool pre = false;	//ǰһ���ַ�Ϊ��д��ĸ?
	for (int i = 0; i < sentence.size(); i++) {
		char ch = sentence[i];
		if (ch >= 'A' && ch <= 'Z') {
			str += ch;
			pre = true;
			//�������
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

//order:��ĸ��˳��
void mycopy(char ch,char** mat,int order) {
	//���ƵĻ�׼��
	int x1 = (ch - 65) * 7 + 1;
	int y1 = 1;
	int x2 = 1;
	int y2 = order * 6 + 1;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 5; j++) {
			mat[i+x2][y2 + j] = m[x1+i][y1+j];
		}
		//����ո�
		mat[i + x2][y2 + 5] = ' ';
	}
}


int main(void) {
	input();
	split();

	int wordnum = words.size();
	//����һ�����󴢴�õ���
	char** mat = new char* [10];
	for (int i = 0; i < 10; i++) {
		mat[i] = new char[100];
	}
	for (int k = 0; k < wordnum; k++) {
		string word = words[k];
		int len = word.size();
		//����ÿ����ĸ���������
		for (int i = 0; i < word.size(); i++) {
			char ch = word[i];
			mycopy(ch, mat, i);
		}
		//�������
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


