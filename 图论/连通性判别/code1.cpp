/*����ͼ����ͨ����*/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

/*�ڵ��������,����Ϊ1000*/
const int max_v=1000;
/*ʵ�ʽڵ����*/
int num_v;
/*����*/
int num_e;
/*�ڽӱ�,ֻ�洢���ӱߵ���һ���ڵ�ı��*/
vector<int> graph[max_v];
/*��ǽڵ���������ͨ����,��ʼ��Ϊ0*/
int comp[max_v]={0};
/*��ǰ������ͨ������id*/
int comp_id=1;
/*��¼�м�����ͨ����*/
int comp_num=0;




/*��ȡstdin���룬���ݴ˽�һ������ͼ���浽�ڽӱ���*/
void input(){
    cin>>num_v>>num_e;

    for(int i=0;i<num_e;i++){
        int v1,v2;
        cin>>v1>>v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
}


/*DFS,�����������Ľڵ����visit״̬*/
void DFS(int v){
    /*�޸�v�ı�־λ*/
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


    cout<<"��ͨ��������: "<<comp_num<<endl;
    for(int i=1;i<=comp_num;i++){
        cout<<"��ͨ����"<<i<<":";
        for(int j=1;j<=num_v;j++){
            if(comp[j]==i)      cout<<j<<",\t";
        }
        cout<<endl;
    }
    

    return 0;
}

