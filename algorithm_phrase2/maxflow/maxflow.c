#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Queue{
    int vertex;//记录节点编号
    int flow;//记录增强路径的最大流量
    struct Queue *next,*pre;
}queue;
int m,value[100][100],capacity[100][100];//value记录流量，capacity记录容量
int pro[100];//前驱子图
void Ford_Fulkerson(int s,int t);
int FindAug(int s,int t);
void first_enqueue(queue** headp,queue** tailp,int vertex);
void enqueue(queue** headp,queue** tailp,int vertex);
void dequeue(queue** headp,queue** tailp);//返回值为找到的增强路径的bottleneck；用BFS找
int main()
{
    int i,j,s,t;//邻接矩阵
    printf("input the numbers of vertices:");scanf("%d",&m);
    printf("Input s and t:");scanf("%d%d",&s,&t);
    printf("Input the adjacent matrix:\n");
    for(i=1;i<=m;i++)
        for(j=1;j<=m;j++)scanf("%d",&capacity[i][j]);
    Ford_Fulkerson(s,t);
    for(i=1;i<=m;i++){
        for(j=1;j<=m;j++)printf("%d ",value[i][j]);printf("\n");}
    return 0;
}
void Ford_Fulkerson(int s,int t)
{
    int min;//记录增加的流量
    while(1){
        if(!(min=FindAug(s,t)))break;
        int walk=t;
        while(pro[walk]!=0){
            if(value[pro[walk]][walk]<capacity[pro[walk]][walk])
                value[pro[walk]][walk]+=min;
            else value[walk][pro[walk]]-=min;
            walk=pro[walk];
        }
    }
}
int FindAug(int s,int t)
{
    int visited[100]={0},i;//记录是否访问过，避免重复访问
    queue *tail,*head=NULL;
    first_enqueue(&head,&tail,s);visited[s]=1;
    while(head){
        for(i=1;i<=m;i++)
            if((value[head->vertex][i]<capacity[head->vertex][i]||
            (value[i][head->vertex]>0))&&visited[i]==0){//利用残差网络的性质
                enqueue(&head,&tail,i);        
                visited[i]=1;      
                if(i==t){return tail->flow;}
            }
        dequeue(&head,&tail);
    }
    return 0;
}
void first_enqueue(queue** headp,queue** tailp,int vertex)
{
    *headp=*tailp=(queue*)malloc(sizeof(queue));
    (*tailp)->vertex=vertex;
    (*headp)->flow=INT_MAX;
    (*headp)->pre=(*headp)->next=NULL;
}
void enqueue(queue** headp,queue** tailp,int vertex)
{    
    queue *head=*headp,*tail=*tailp;
    tail->next=(queue*)malloc(sizeof(queue));
    tail->next->pre=tail;
    tail->next->vertex=vertex;
    int sim;//sim for simple
    if(value[head->vertex][vertex]<capacity[head->vertex][vertex])
        sim=capacity[head->vertex][vertex]-value[head->vertex][vertex];
    else sim=value[vertex][head->vertex];//注意区分两个vertex
    tail->next->flow=fmin(head->flow,sim);//sim是为了使表达式尽量简单
    tail=tail->next;
    pro[tail->vertex]=head->vertex;
    tail->next=NULL;
    *headp=head,*tailp=tail;
}
void dequeue(queue** headp,queue** tailp)
{
    queue *head=*headp,*tail=*tailp;
    if(head!=NULL){ 
        queue* save=head;
        head=head->next;
        free(save); 
        if(head!=NULL)head->pre=NULL;
    }
    *headp=head,*tailp=tail;
}