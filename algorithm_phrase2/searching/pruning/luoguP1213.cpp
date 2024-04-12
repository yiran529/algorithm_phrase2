#include<iostream>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
#include<unordered_map>
#include<cmath>
using namespace std;
typedef struct MATRIX{
    int a[10];
    bool operator<(struct MATRIX x) const{
        int ret=0;
        for(int i=1;i<=9;i++)if(x.a[i]!=a[i])return a[i]<x.a[i];
        return false;
    }
    bool operator==(struct MATRIX x) const{
        int ret=0;
        for(int i=1;i<=9;i++)if(x.a[i]!=a[i])return false;
        return true;
    }
}matrix;
long long ee=1e9;
long long pw[10]={0,10,100,1000,10000,100000,1000000,1000000,10000000,100000000};
struct matrixHash {
     size_t operator () (const matrix &t) const {
         long long ret=0;
         for(int i=1;i<=9;i++)ret+=t.a[i]*pw[i];
         return ret;
     }
};
int h(matrix x){
    int ret=0;
    for(int i=1;i<=9;i++) 
        if(x.a[i]!=12)ret=fmax(ret,(12-x.a[i])/3);
    return ret;
}
typedef struct NODE{
    matrix cl;
    matrix pa;
    int chg;
    int g;
    bool operator<(struct NODE y) const{
        //return g+h(cl)>y.g+h(y.cl);
        return g>=y.g;
    }
}node;
typedef struct INFO{
    int first;matrix second;
}info;
matrix init;
int main()
{
    for(int i=1;i<=9;i++)cin>>init.a[i];
    int ch[10][10];
    ch[1][0]=4;ch[1][1]=1;ch[1][2]=2;ch[1][3]=4;ch[1][4]=5;
    ch[2][0]=3;ch[2][1]=1;ch[2][2]=2;ch[2][3]=3;
    ch[3][0]=4;ch[3][1]=2;ch[3][2]=3;ch[3][3]=5;ch[3][4]=6;
    ch[4][0]=3;ch[4][1]=1;ch[4][2]=4;ch[4][3]=7;
    ch[5][0]=5;ch[5][1]=2;ch[5][2]=4;ch[5][3]=5;ch[5][4]=6;ch[5][5]=8;
    ch[6][0]=3;ch[6][1]=3;ch[6][2]=6;ch[6][3]=9;
    ch[7][0]=4;ch[7][1]=4;ch[7][2]=5;ch[7][3]=7;ch[7][4]=8;
    ch[8][0]=3;ch[8][1]=7;ch[8][2]=8;ch[8][3]=9;
    ch[9][0]=4;ch[9][1]=5;ch[9][2]=6;ch[9][3]=8;ch[9][4]=9;
    node first=(node){init,init,0,0};
    queue<node> q;
    q.push(first);
    unordered_map<matrix,info,matrixHash> mp;//记录每一个在closed集中的状态的父亲状态以及相应的变化的编号
    while(!q.empty()){
        node cur=q.front();
        q.pop();
        if(mp.find(cur.cl)!=mp.end())continue;//In the closed set
        mp[cur.cl]={cur.chg,cur.pa};//Put into the closed set
       // mp[cur.cl].first=cur.chg;
        //cout<<mp[cur.cl].first<<endl;
        if(!h(cur.cl)){
            matrix p=cur.cl;int ans[100000],cnt=0;
            while(mp[p].first){
                ans[++cnt]=mp[p].first;
                p=mp[p].second;
            }
            for(int i=cnt;i>=1;i--)cout<<ans[i]<<" ";
            break;
        }
        matrix newMat;
        for(int j=1;j<=9;j++)newMat.a[j]=cur.cl.a[j];
        for(int i=1;i<=9;i++){
            for(int j=1;j<=ch[i][0];j++){
                int x=ch[i][j];
                newMat.a[x]=(newMat.a[x]+3)%12;
                if(newMat.a[x]==0)newMat.a[x]=12;
            }
            if(mp.find(newMat)==mp.end())q.push((node){newMat,cur.cl,i,cur.g+1});
            for(int j=1;j<=ch[i][0];j++){
                int x=ch[i][j];
                newMat.a[x]=(newMat.a[x]-3+12)%12;
                if(newMat.a[x]==0)newMat.a[x]=12;
            }
        }
    }
    return 0;
}