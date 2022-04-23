#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
using namespace std;


/*����һ����*/
struct edge{
	int v;	//�ڵ��ţ���0��ʼ 
	int w;	//��Ȩ 
	edge(int x,int y):v(x),w(y){}
};

#define MAX 2000
//���� 
int N=0;	
//��ֵ 
int K=0;
//�ڽӱ� 
vector<edge> adj[MAX];
//����-���map
map<string,int> map1; 
//���-����map
map<int,string> map2;
//��Ȩ����
int vw[MAX]={0}; 
//input�м�¼�Ѿ��ж��ٽڵ�
int mycount=0; 
//��ǰ��֪��ͨ������
int compnum=0; 
//leader-�ڵ���map 
map<string,int> map3;
//�ҵ�������������������ͨ����
vector<int> comp[MAX]; 
//��ǽڵ��Ƿ񱻷��ʹ�
bool visit[MAX]={false}; 

using namespace std;

/*�ж������Ƿ���map�У������ر�š������ֲ���map�У������ּ���map1��map2*/
int inmap(string name){
	map<string,int>::iterator iter=map1.find(name);
	if(iter==map1.end()){
		map1.insert(pair<string,int>(name,mycount));
		map2.insert(pair<int,string>(mycount,name));
		return mycount++;
	}
	else{
		return (*iter).second;
	}
}

/*��ȡ����*/
void input(){
	cin>>N>>K;
	string name1,name2;
	int w;
	for(int i=0;i<N;i++){
		cin>>name1>>name2>>w;
		int v1=inmap(name1);
		int v2=inmap(name2);
		/*���±߼����ڽӱ�*/
		bool flag=true;
		for(int i=0;i<adj[v1].size();i++){
			if(adj[v1][i].v==v2){
				adj[v1][i].w+=w;
				flag=false;
				break;
			}			
		}
		if(flag)
			adj[v1].push_back(edge(v2,w));
			
		flag=true;	
		for(int i=0;i<adj[v2].size();i++){
			if(adj[v2][i].v==v1){
				adj[v2][i].w+=w;
				flag=false;
				break;
			}			
		}
		if(flag)
			adj[v2].push_back(edge(v1,w));
		/*�����Ȩ*/
		vw[v1]+=w;
		vw[v2]+=w;		
	}
}

/*����DFS��ȡ������������ͨ������Ա�������Ȩ��*/
int DFS(int u){
	visit[u]=true;
	comp[compnum].push_back(u);
	
	
	//��ǰ�ܱ�Ȩ 
	int totalweight=0;
	for(int i=0;i<adj[u].size();i++){
		int v=adj[u][i].v;
		totalweight+=adj[u][i].w;
		
		//����Ȩ��Ϊ0
			adj[u][i].w=0;
			for(int j=0;j<adj[v].size();j++){
				if(adj[v][j].v==u){
					adj[v][j].w=0;
					break;
				}
			}
		
		//��δ�����ʹ��Ľڵ������ͨ���� 
		if(!visit[v]){			
			//����DFS
			totalweight+=DFS(v); 			
		}
		
	}
	
	return totalweight;
}

/*��ͼDFS���ҵ�����������������ͨ�������������comp*/
void find(){
	for(int i=0;i<N;i++){
		if(!visit[i]){
			int totalweight=DFS(i);
			if(totalweight<=K || comp[compnum].size()<=2){
				//ɾ���¼���ķ��� 
				comp[compnum].clear();
				continue;
			}
			
			compnum++;
		}
	}
}

/*���map3*/
void getleader(){
	//����comp����,��ȡÿ����ͨ������leader
	for(int j=0;j<compnum;j++) {
		vector<int> vec=comp[j];
		//��ǰ��Ȩ�����ֵ 
		int temp=0;
		//leader�ı�� 
		int leader;
		for(int i=0;i<vec.size();i++){
			int u = vec[i];
			if(vw[u]>temp){
				temp=vw[u];
				leader=u;
			}
		}
		//��leader����Ϣ����map3
		string leadername=map2.find(leader)->second;
		map3.insert(pair<string,int>(leadername,vec.size()));
	}
}



int main(void){
	input();
	find();
	getleader();
	
	//����map3���������]
	cout<<map3.size()<<endl;
	for(map<string,int>::iterator iter=map3.begin();iter!=map3.end();iter++) {
		cout<<iter->first<<" "<<iter->second<<endl;
	}
	
	return 0;
}
