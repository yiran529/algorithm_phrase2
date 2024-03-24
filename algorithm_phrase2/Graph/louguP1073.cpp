#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> s[100001],e[100001];
int val[100001];
int minn[100001];
int maxx[100001];
int n,m;//n表示城市数目，m表示道路数目
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%d",&val[i]);
    for(int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        s[x].push_back(y);
        e[y].push_back(x);
        if(z==2){
            e[x].push_back(y);
            s[y].push_back(x);
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=0;j<=e[i].size()-1;j++)cout<<e[i][j]<<" ";
    //     cout<<endl;
    // }
    queue<int> q;
    bool inQ[100001];
    memset(inQ,0,sizeof(bool)*100001);
    memset(minn,127,sizeof(int)*100001);
    q.push(1);
    inQ[1]=1;
    minn[1]=val[1];
    while(q.size()){
        int cur=q.front();
        q.pop();
        inQ[cur]=0;
        int l=s[cur].size()-1;
        for(int i=0;i<=l;i++){
            if(minn[s[cur][i]]>minn[cur]){
                minn[s[cur][i]]=fmin(minn[cur],val[s[cur][i]]);
                if(!inQ[s[cur][i]]){ 
                    inQ[s[cur][i]]=1;
                    q.push(s[cur][i]);
                }
            }
        }
    }
    memset(inQ,0,sizeof(bool)*100001);
    memset(maxx,-1,sizeof(int)*100001);
    q.push(n);
    inQ[n]=1;
    maxx[n]=val[n];
    while(q.size()){
        int cur=q.front();
        q.pop();
        inQ[cur]=0;
        int l=e[cur].size()-1;
        for(int i=0;i<=l;i++){ 
            if(maxx[e[cur][i]]<maxx[cur]){
                maxx[e[cur][i]]=fmax(maxx[cur],val[e[cur][i]]);
                if(!inQ[e[cur][i]]){ 
                    inQ[e[cur][i]]=1;
                    q.push(e[cur][i]);
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)ans=fmax(ans,maxx[i]-minn[i]);
    cout<<ans;
    return 0;
}