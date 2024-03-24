#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<climits>
#include<queue>
#include<cstring>
#include<climits>
#define N 105
using namespace std;
unsigned int n,k,m,s,t;
unsigned int repel[N][N];
bool learned[N];
struct DIS{//包含了一个点的目的地的信息
    unsigned int destination;
    unsigned int distance;
}dis[N][N];
unsigned int desNum[N];
unsigned int culture[N];
bool inQ[N];
unsigned int Tdis[N];
unsigned int ans;
void spfa()//Bellman-Ford算法的改进
{
    queue<unsigned int> Q;
    Q.push(t);
    inQ[t]=true;
    memset(Tdis,0x7f,sizeof(Tdis));//为什么是0x7f?
    Tdis[t]=0;  
    while(Q.size()){
        unsigned int curNode=Q.front();
        Q.pop();
        inQ[curNode]=false;//DO NOT FORGET ABOUT THIS!
        for(unsigned int i=1;i<=desNum[curNode];i++){
            if(Tdis[dis[curNode][i].destination]>dis[curNode][i].distance+Tdis[curNode]){
                Tdis[dis[curNode][i].destination]=dis[curNode][i].distance+Tdis[curNode];
                if(!inQ[dis[curNode][i].destination]){//注意这个判断的位置
                    inQ[dis[curNode][i].destination]=true;
                    Q.push(dis[curNode][i].destination);
                }
            }
        }
    }
}
bool check(unsigned int node){
    int curCul=culture[node];
    for(int i=1;i<=repel[curCul][0];i++){
        if(learned[repel[curCul][i]])return false;
    }
    return true;
}
void dfs(unsigned int curNode,unsigned int curCost){
    if(curNode==t){
        ans=fmin(ans,curCost);
        return;
    }
    if(curCost+Tdis[curNode]>=ans)return;//强剪枝
    for(int i=1;i<=desNum[curNode];i++){
        int nextNode=dis[curNode][i].destination;
        if(!learned[culture[nextNode]]&&check(nextNode)){
            learned[culture[nextNode]]=true;
            dfs(nextNode,curCost+dis[curNode][i].distance);
            learned[culture[nextNode]]=false;
        }
    }
}
int main()
{
    int i;
    scanf("%u%u%u%u%u",&n,&k,&m,&s,&t);
    for(i=1;i<=n;i++)scanf("%u",&culture[i]);
    for(i=1;i<=k;i++){
        repel[i][0]=0;
        for(int j=1;j<=k;j++){
            int tem;
            scanf("%d",&tem);
            if(tem==1){
                repel[i][0]++;
                repel[i][repel[i][0]]=j;
            }
        }
    }
    for(i=1;i<=m;i++){
        unsigned int x,y,d;
        scanf("%u%u%u",&x,&y,&d);
        desNum[x]++;
        dis[x][desNum[x]]=(DIS){y,d};
        desNum[y]++;
        dis[y][desNum[y]]=(DIS){x,d};
    }
    spfa();
    ans=INT_MAX;
    learned[culture[s]]=true;
    dfs(s,0);
    if(ans==INT_MAX)printf("-1");
    else printf("%u",ans);
    return 0;
}