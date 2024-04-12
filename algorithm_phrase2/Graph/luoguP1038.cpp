#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#define N 200
using namespace std;
int n,p,c[N],u,indg[N],outdg[N];
vector<pair<int,int>> edge[N];
int main()
{
    cin>>n>>p;
    for(int i=1;i<=n;i++){
        cin>>c[i]>>u;
        if(c[i]==0)c[i]-=u;
    }
    for(int i=1;i<=p;i++){
        int x,y,z;
        cin>>x>>y>>z;
        edge[x].push_back(make_pair(y,z));
        indg[y]++,outdg[x]++;
    }
    queue<int> q;
    for(int i=1;i<=n;i++)if(indg[i]==0)q.push(i);
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        int l=edge[cur].size();
        for(int i=0;i<l;i++){
            int next=edge[cur][i].first;
            indg[next]--;
            if(indg[next]==0)q.push(next);
            if(c[cur]>0)c[next]+=c[cur]*edge[cur][i].second;
        }
    }  
    int flag=0;
    for(int i=1;i<=n;i++){
        if(outdg[i]==0&&c[i]>0){flag=1;cout<<i<<" "<<c[i]<<endl;}
    }
    if(flag==0)cout<<"NULL";
    return 0;
}