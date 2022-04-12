/*寻找所有强连通分量*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int v_max=1000;


/*节点的最大个数,假设为1000*/
const int max_v=1000;
/*实际节点个数*/
int num_v;
/*边数*/
int num_e;
/*邻接表,只存储连接边的另一个节点的编号*/
vector<int> graph[max_v+1];
/*标记节点所属的连通分量,初始化为0*/
int comp[max_v+1]={0};
/*当前所属连通分量的id*/
int comp_id=1;
/*记录有几个连通分量*/
int comp_num=0;
/*dfn数组*/
int dfn[max_v+1]={0};
/*low数组*/
int low[max_v+1]={0};
/*存储节点编号的栈*/
stack<int> mystack;
/*时间戳*/
int order=1;
/*节点是否已在栈中*/
bool instack[max_v+1]={false};


/*读取stdin输入，根据此将一个无向图储存到邻接表中*/
void input(){
    cin>>num_v>>num_e;

    for(int i=0;i<num_e;i++){
        int v1,v2;
        cin>>v1>>v2;
        graph[v1].push_back(v2);
        //graph[v2].push_back(v1);      有向图不能这么写
    }
}

int min(int i,int j){return i<j ? i : j;}

void tarjan(int v_id){
    /*visit到新的节点,将dfn和low中对应的值初始化为相等的*/
    dfn[v_id]=order;
    low[v_id]=order;
    order++;
    /*更新instack数组*/
    instack[v_id]=true;
    /*当前节点进栈*/
    mystack.push(v_id);

    /*进行dfs*/
    for(int i=0;i<graph[v_id].size();i++){
        int next = graph[v_id][i];
        /*与v_id相邻的节点没有被visit过*/
        if(dfn[next]==0){
            tarjan(next);
            /*更新low值*/
            low[v_id]=min(low[v_id],low[next]);
        }
        /*与v_id相邻的节点已经在栈中(有环)*/
        else if(instack[next]){
            low[v_id]=min(low[v_id],dfn[next]);
        }
    }

    /*判断以v_id为root的子树是否为一个强连通分量*/
    if(low[v_id]==dfn[v_id]){
        /*一直pop stack直到把v_id对应的节点pop出来*/
        while(true){
            int i=mystack.top();
            mystack.pop();
            instack[i]=false;       /*更新栈*/
            /*更新comp数组，增加新的强连通分量*/
            comp[i]=comp_id;

            if(i==v_id)      break;                
        }
        comp_id++;
        comp_num++;
    }
}



int main(void){
    input();

    for(int i=1;i<=num_v;i++){
        if(comp[i]==0)
            tarjan(i);
    }

    cout<<"强连通分量数量: "<<comp_num<<endl;
    for(int i=1;i<=comp_num;i++){
        cout<<"强连通分量"<<i<<":";
        for(int j=1;j<=num_v;j++){
            if(comp[j]==i)      cout<<j<<",\t";
        }
        cout<<endl;
    }

    return 0;
}