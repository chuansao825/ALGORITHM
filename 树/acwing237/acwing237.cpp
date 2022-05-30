#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<unordered_map>		
#include<vector>

using namespace std;

int t;
//ʹ�ù�ϣ����ɢ����������,keyΪ����ţ�valueΪ�����ı�ţ�ע�⣬ÿ��ѭ������Ҫclear
unordered_map<int, int> father;
//���浱ǰ�ж������в�����������ע�⣬ÿ��ѭ������Ҫclear
vector<pair<int, int>> neq;


//ʹ��·��ѹ��
int findfather(int i) {
	if (father[i] == i)	return i;
	int root = findfather(father[i]);
	father[i] = root;
	return root;
}

//�ж������ڵ��Ƿ���ͬһ��set��
bool find(int i,int j) {
	return findfather(i) == findfather(j);
}

//union����set
void myunion(int i,int j) {
	if (!find(i, j)) {
		int r1, r2;
		r1 = findfather(i);
		r2 = findfather(j);
		father[r2] = r1;
	}
}

//��i��j����father�����Ѵ����򲻴�����������벢��ʼ��
void add(int i, int j) {
	if (father.find(i) == father.end()) {
		father.insert(pair<int, int>(i, i));
	}
	if (father.find(j) == father.end()) {
		father.insert(pair<int, int>(j, j));
	}
}

int main(void) {
	//�ر�ͬ��������io
	ios::sync_with_stdio(false);

	cin >> t;
	while (t-- > 0) {
		//������
		int qnum;
		cin >> qnum;
		int i, j, e;
		while (qnum-- > 0) {
			cin >> i >> j >> e;
			if (e == 1) {
				//����ɢ�����棬Ȼ��union
				add(i, j);
				myunion(i, j);
			}
			else if (e == 0) {
				//����ɢ�����棬Ȼ��洢����ȵ�����
				add(i, j);
				neq.push_back(pair<int, int>(i, j));
			}
		}

		//�������в����ڵ��������жϽڵ��Ƿ���һ��set��
		bool flag=true;
		for (int k = 0; k < neq.size(); k++) {
			int i, j;
			i = neq[k].first;
			j = neq[k].second;
			if (find(i, j)) {
				flag = false;
				break;
			}
		}

		if (flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;

		//���father��neq����
		father.clear();
		neq.clear();
	}
}
