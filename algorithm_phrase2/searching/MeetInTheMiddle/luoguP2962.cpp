#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<climits>
#include<cmath>
#define ll long long 
using namespace std;
vector<int> edge[100];
map<ll,ll> mp;
int n,m;ll ans=LONG_LONG_MAX;
void dfs(ll cur,ll step,int cnt,int sign){
    if(sign==0&&cnt==n/2+1){
        if(!mp[cur])mp[cur]=step+1;else mp[cur]=fmin(mp[cur],step+1);
        return;
    }
    else if(sign==1&&cnt==n+1){
        ll com=cur^(ll)(((ll)1<<n)-1);
        if(mp[com]&&step+mp[com]<ans)ans=step-1+mp[com];
        return;
    }
    dfs(cur,step,cnt+1,sign);
    cur^=(ll)1<<(cnt-1);
    int l=edge[cnt].size();
    for(int i=0;i<l;i++){
        int neigh=edge[cnt][i];
        //if(cnt==18)cout<<neigh<<endl;
        cur^=(ll)1<<(neigh-1);
    }
    dfs(cur,step+1,cnt+1,sign);
}
int main()
{
    cin>>n>>m;
    //int deb=-1;
    for(int i=1;i<=m;i++){
        int s,t;cin>>s>>t;
        edge[s].push_back(t);
        edge[t].push_back(s);
        //if(edge[s].size()==n-1)deb=s;
        //if(edge[t].size()==n-1)deb=t;
    }
    dfs(0,0,1,0);
    dfs(0,0,n/2+1,1); 
    cout<<ans<<endl;
    //cout<<deb;
    //cout<<();
    return 0;
}//||)mp.find(0)!=mp.end()