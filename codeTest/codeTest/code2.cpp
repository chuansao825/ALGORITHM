/*Ѱ������ǿ��ͨ����*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int v_max=1000;


/*�ڵ��������,����Ϊ1000*/
const int max_v=1000;
/*ʵ�ʽڵ����*/
int num_v;
/*����*/
int num_e;
/*�ڽӱ�,ֻ�洢���ӱߵ���һ���ڵ�ı��*/
vector<int> graph[max_v+1];
/*��ǽڵ���������ͨ����,��ʼ��Ϊ0*/
int comp[max_v+1]={0};
/*��ǰ������ͨ������id*/
int comp_id=1;
/*��¼�м�����ͨ����*/
int comp_num=0;
/*dfn����*/
int dfn[max_v+1]={0};
/*low����*/
int low[max_v+1]={0};
/*�洢�ڵ��ŵ�ջ*/
stack<int> mystack;
/*ʱ���*/
int order=1;
/*�ڵ��Ƿ�����ջ��*/
bool instack[max_v+1]={false};


/*��ȡstdin���룬���ݴ˽�һ������ͼ���浽�ڽӱ���*/
void input(){
    cin>>num_v>>num_e;

    for(int i=0;i<num_e;i++){
        int v1,v2;
        cin>>v1>>v2;
        graph[v1].push_back(v2);
        //graph[v2].push_back(v1);      ����ͼ������ôд
    }
}

int min(int i,int j){return i<j ? i : j;}

void tarjan(int v_id){
    /*visit���µĽڵ�,��dfn��low�ж�Ӧ��ֵ��ʼ��Ϊ��ȵ�*/
    dfn[v_id]=order;
    low[v_id]=order;
    order++;
    /*����instack����*/
    instack[v_id]=true;
    /*��ǰ�ڵ��ջ*/
    mystack.push(v_id);

    /*����dfs*/
    for(int i=0;i<graph[v_id].size();i++){
        int next = graph[v_id][i];
        /*��v_id���ڵĽڵ�û�б�visit��*/
        if(dfn[next]==0){
            tarjan(next);
            /*����lowֵ*/
            low[v_id]=min(low[v_id],low[next]);
        }
        /*��v_id���ڵĽڵ��Ѿ���ջ��(�л�)*/
        else if(instack[next]){
            low[v_id]=min(low[v_id],dfn[next]);
        }
    }

    /*�ж���v_idΪroot�������Ƿ�Ϊһ��ǿ��ͨ����*/
    if(low[v_id]==dfn[v_id]){
        /*һֱpop stackֱ����v_id��Ӧ�Ľڵ�pop����*/
        while(true){
            int i=mystack.top();
            mystack.pop();
            instack[i]=false;       /*����ջ*/
            /*����comp���飬�����µ�ǿ��ͨ����*/
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

    cout<<"ǿ��ͨ��������: "<<comp_num<<endl;
    for(int i=1;i<=comp_num;i++){
        cout<<"ǿ��ͨ����"<<i<<":";
        for(int j=1;j<=num_v;j++){
            if(comp[j]==i)      cout<<j<<",\t";
        }
        cout<<endl;
    }

    return 0;
}