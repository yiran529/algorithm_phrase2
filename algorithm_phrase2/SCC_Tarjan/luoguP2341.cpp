#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<stack>
#define N 50003
using namespace std;
vector<int> To[N],SCCv[N];
bool inStack[N],visited[N];
int low[N],dfn[N],time,sccNum,n,m,SCCtag[N];
stack<int> st;
void sccdfs(int u){//Tarjan算法
    st.push(u);
    low[u]=dfn[u]=++time;
    inStack[u]=true;
    visited[u]=true;
    int l=To[u].size();
    for(int i=0;i<l;i++){
        int v=To[u][i];
        if(!visited[v]){//树边
            sccdfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(inStack[v])//不是树边，也不是横向边，也不是前向边，这保证了是后向边，指向u的祖先
            low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        int top;
        sccNum++;
        do{   
            top=st.top();
            inStack[top]=false;
            st.pop();
            SCCtag[top]=sccNum;
            SCCv[sccNum].push_back(top);
        }while(top!=u);
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        To[x].push_back(y);
    }
    for(int i=1;i<=n;i++)
        if(!visited[i])sccdfs(i);
    int ans=0;
    for(int i=1;i<=sccNum;i++){
        bool flag=true;
        int l=SCCv[i].size();
        for(int j=0;j<l;j++){
            int node=SCCv[i][j];
            int e=To[node].size();
            for(int z=0;z<e;z++){
                if(SCCtag[To[node][z]]!=i){flag=false;break;}
            }
            if(flag==false)break;
        }
        if(flag==true){
            if(ans==0)ans=l;
            else {ans=0;break;}
        }
    }
    cout<<ans;
    return 0;
}