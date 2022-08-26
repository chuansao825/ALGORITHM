#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;


const int MAX = 105;
//ģʽ�ַ���
string pattern;
//��Сд����ѡ��
int sens;
//����
int n;
//��ǰ�����ַ���
string str;
//next����
int nex[MAX] = { 0 };

//���������жϵ��������ж����ַ��Ƿ����
bool equal(char a,char b) {
	//�ж����п���
	if (sens) {
		return a == b;
	}
	else {
		if (a < 'a')	a += 32;
		if (b < 'a')	b += 32;
		return a == b;
	}
}

//��ʼ��next����
void init_next() {
	int len = pattern.size();
	nex[0] = -1;
	int j = -1;
	for (int i = 1; i < len; i++) {
		while (j!=-1 && !equal(pattern[i],pattern[j+1])) {
			j = nex[j];
		}
		if (equal(pattern[j+1],pattern[i])) {
			j++;
		}
		nex[i] = j;
	}
}

//�ж��ַ����Ƿ�ƥ��
bool cmp() {
	int j = -1;
	for (int i = 0; i < str.size(); i++) {
		while (j != -1 && !equal(str[i], pattern[j + 1])) {
			j = nex[j];
		}
		if (equal(str[i],pattern[j+1])) {
			j++;
		}
		if (j == pattern.size() - 1)
			return true;
	}
	return false;
}

int main(void) {
	ios::sync_with_stdio(false);
	cin >> pattern;
	cin >> sens >> n;

	//����pattern��next����
	init_next();
	for (int i = 0; i < n; i++) {
		cin >> str;
		if (cmp())
			cout << str<<endl;
	}
}