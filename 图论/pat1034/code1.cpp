#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
using namespace std;


/*储存一条边*/
struct edge{
	int v;	//节点编号，从0开始 
	int w;	//边权 
	edge(int x,int y):v(x),w(y){}
};

#define MAX 2000
//人数 
int N=0;	
//阈值 
int K=0;
//邻接表 
vector<edge> adj[MAX];
//姓名-编号map
map<string,int> map1; 
//编号-姓名map
map<int,string> map2;
//点权数组
int vw[MAX]={0}; 
//input中记录已经有多少节点
int mycount=0; 
//当前已知连通分量数
int compnum=0; 
//leader-节点数map 
map<string,int> map3;
//找到的所有满足条件的连通分量
vector<int> comp[MAX]; 
//标记节点是否被访问过
bool visit[MAX]={false}; 

using namespace std;

/*判断名字是否在map中，并返回编号。若名字不在map中，将名字加入map1和map2*/
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

/*读取输入*/
void input(){
	cin>>N>>K;
	string name1,name2;
	int w;
	for(int i=0;i<N;i++){
		cin>>name1>>name2>>w;
		int v1=inmap(name1);
		int v2=inmap(name2);
		/*将新边加入邻接表*/
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
		/*计算点权*/
		vw[v1]+=w;
		vw[v2]+=w;		
	}
}

/*利用DFS获取满足条件的联通分量成员，计算边权和*/
int DFS(int u){
	visit[u]=true;
	comp[compnum].push_back(u);
	
	
	//当前总边权 
	int totalweight=0;
	for(int i=0;i<adj[u].size();i++){
		int v=adj[u][i].v;
		totalweight+=adj[u][i].w;
		
		//将边权设为0
			adj[u][i].w=0;
			for(int j=0;j<adj[v].size();j++){
				if(adj[v][j].v==u){
					adj[v][j].w=0;
					break;
				}
			}
		
		//将未被访问过的节点加入连通分量 
		if(!visit[v]){			
			//继续DFS
			totalweight+=DFS(v); 			
		}
		
	}
	
	return totalweight;
}

/*对图DFS，找到所有满足条件的连通分量，将其加入comp*/
void find(){
	for(int i=0;i<N;i++){
		if(!visit[i]){
			int totalweight=DFS(i);
			if(totalweight<=K || comp[compnum].size()<=2){
				//删掉新加入的分量 
				comp[compnum].clear();
				continue;
			}
			
			compnum++;
		}
	}
}

/*完成map3*/
void getleader(){
	//遍历comp集合,获取每个连通分量的leader
	for(int j=0;j<compnum;j++) {
		vector<int> vec=comp[j];
		//当前点权的最大值 
		int temp=0;
		//leader的编号 
		int leader;
		for(int i=0;i<vec.size();i++){
			int u = vec[i];
			if(vw[u]>temp){
				temp=vw[u];
				leader=u;
			}
		}
		//将leader的信息加入map3
		string leadername=map2.find(leader)->second;
		map3.insert(pair<string,int>(leadername,vec.size()));
	}
}



int main(void){
	input();
	find();
	getleader();
	
	//遍历map3，输出数据]
	cout<<map3.size()<<endl;
	for(map<string,int>::iterator iter=map3.begin();iter!=map3.end();iter++) {
		cout<<iter->first<<" "<<iter->second<<endl;
	}
	
	return 0;
}
