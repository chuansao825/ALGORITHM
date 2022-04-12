/*无向图的连通分量*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

/*节点的最大个数,假设为1000*/
const int max_v=1000;
/*实际节点个数*/
int num_v;
/*边数*/
int num_e;
/*邻接表,只存储连接边的另一个节点的编号*/
vector<int> graph[max_v];
/*标记节点所属的连通分量,初始化为0*/
int comp[max_v]={0};
/*当前所属连通分量的id*/
int comp_id=1;
/*记录有几个连通分量*/
int comp_num=0;




/*读取stdin输入，根据此将一个无向图储存到邻接表中*/
void input(){
    cin>>num_v>>num_e;

    for(int i=0;i<num_e;i++){
        int v1,v2;
        cin>>v1>>v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
}


/*DFS,并将遍历到的节点更新visit状态*/
void DFS(int v){
    /*修改v的标志位*/
    comp[v]=comp_id;
    for(int i=0;i<graph[v].size();i++){
        int to=graph[v][i];
        if(!comp[to]){
            DFS(to);
        }
    }
}



int main(void){
    input();

    for(int i=1;i<=num_v;i++){
        if(comp[i]==0){
            DFS(i);
            comp_num++;
            comp_id++;
        }        
    }


    cout<<"连通分量数量: "<<comp_num<<endl;
    for(int i=1;i<=comp_num;i++){
        cout<<"连通分量"<<i<<":";
        for(int j=1;j<=num_v;j++){
            if(comp[j]==i)      cout<<j<<",\t";
        }
        cout<<endl;
    }
    

    return 0;
}

