#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
#pragma GCC optimize(2)
using namespace std;

typedef long long ll;
const int MAXLEN = 1000005;
const int MAXNUM = 35;
int strnum=0;		//�ַ���������
//�����������ַ���
string s1, s2;
//���
int result[MAXNUM] = { 0 };
//������
ll p = 10000019;
//mod
ll mod = 1000000007;
//H���飬H[i]��ʾ�ַ���ǰi���ַ����Ӵ���hashֵ
ll H1[MAXLEN] = { 0 }, H2[MAXLEN] = { 0 };
//powp[i]��ʾp��i�η�
ll powp[MAXLEN] = { 0 };

//�����ַ�����H����
void calH(ll* H,string& str) {
	H[0] = str[0];
	for (int i = 1; i < str.size(); i++) {
		H[i] = (H[i - 1] * p + str[i]) % mod;
	}
}

//���,Ԥ�����p���ݴ�
void getpowp() {
	powp[0] = 1;
	for (int i = 1; i < MAXLEN; i++) {
		powp[i] = (powp[i - 1] * p)%mod;
	}
}

//�����Ӵ��Ĺ�ϣֵ
ll calsubH(ll* H,int i,int j){
	//��iΪ0��������⴦��
	if (i == 0)
		return H[j];
	else
		return ((H[j] - H[i - 1] * powp[j - i + 1]) % mod + mod) % mod;
}

//�Ƚ������Ӵ��Ƿ����
bool cmp(int i1,int j1,int i2,int j2) {
	return calsubH(H1, i1, j1) == calsubH(H2, i2, j2);	
}

//���ַ�������Ԥ����ÿ�����ַ�֮�����һ��'#'
void initstring(string& tmp,int& len) {
	len = 2 * len - 1;
	char* ch = new char[len + 1];
	for (int i = 0; i < len; i++) {
		if (i % 2 == 0)	ch[i] = tmp[i / 2];
		else    ch[i] = '#';
	}
	ch[len] = '\0';
	tmp = string(ch);
}

//�����Ե�i���ַ�Ϊ����ʱ�������Ӵ�����󳤶�
//�ַ���s1���ַ���s2Ϊ�䷴��
int calbyi(int i,int len) {
	//�����������Сֵ�����ֵ
	int lb = 0, rb = min(i, len - i-1);	
	//�ִ��İ뾶(���������ĵ�)��ע������ʼ��Ӧ��i=0�����
	int k=0;
	
	//ʹ�ö��ַ����
	while (rb > lb) {
		//ע��뾶Ҫ���ڵ���1,������ڵ�һ����֧����ѭ��
		k = (lb + rb) / 2+1;
		//���������ִ���Ҫ�Ƚϵ��Ӵ��Ŀ�ʼλ��
		int b1 = i - k, b2 = len - k - (i + 1);
		//�ж��Ӵ���ϣֵ�Ƿ����
		if (cmp(b1,b1+k-1,b2,b2+k-1)) {
			//��iΪ���ģ�kΪ�뾶���Ӵ��ǻ����Ӵ���������������չ(�ö��ֵķ���)
			//�����޸��������Сֵ����ʾ�뾶������k���ַ�
			lb = k;
		}
		else {
			//��iΪ���ģ�kΪ�뾶���Ӵ����ǻ����Ӵ������������������뾶
			//�޸���������ֵ����ʾ�뾶ҪС��k���ַ�
			rb = k - 1;
		}		
	}

	//�����'#'��Ļ����Ӵ��ĳ���,ע������뾶������k����Ϊ�����˳�ѭ��ʱ����k��ֵ������ȷ�뾶
	//Ҫ���������ַ����������ж�
	//����Ϊ'#'�������Ӵ�Ϊż������
	if (s1[i] == '#') {
		return ((lb + 1) / 2) * 2;
	}
	//����ΪӢ���ַ������Ĵ�Ϊ��������
	else{
		return 2*(lb/2) + 1;
	}
}

//�����ַ���s1��������ִ�����
int cal(int len) {
	int maxlen=1;	//���Ĵ�����󳤶�
	//�������е㣬������Ϊ���ĵ����
	for (int i = 0; i < len; i++) {
		maxlen = max(calbyi(i,len), maxlen);
	}
	return maxlen;
}


int main(void) {
	ios::sync_with_stdio(false);
	getpowp();		//���

	//��s1,s2Ԥ���ռ����Ż�
	s1.reserve(MAXLEN);
	s2.reserve(MAXLEN);

	//�������ַ��������������Ӵ�����
	string inputstr;
	int strnum = 0;
	int len = 0;
	while(true) {
		getline(cin, s1);
		if (s1 == "END")		break;
		//ԭʼ�ַ����ͷ����ַ���
		len = s1.size();
		initstring(s1,len);		//���ַ�֮�����'#'
		s2 = s1;
		reverse(s2.begin(), s2.end());
		//���������ַ�����H����
		calH(H1, s1);
		calH(H2, s2);
		//���
		result[++strnum]=cal(len);
	}
	
	//������
	for (int i = 1; i <= strnum; i++) {
		cout << "Case " << i << ": " << result[i] << endl;
	}
}