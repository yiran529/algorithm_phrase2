#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
#define N 200005
int root,n,minn,cnt,tr[N*8],lc[N*8],rc[N*8],delta;
void ins(int l,int r,int &p,int tar){
    if(p==0)p=++cnt;
    tr[p]++;
    if(l==r)return;
    int mid=(l+r)/2;
    if(mid>=tar)  ins(l,mid,lc[p],tar);
    else          ins(mid+1,r,rc[p],tar);
}
int kth(int l,int r,int p,int k){
    if(l==r)return l;
    int s=tr[rc[p]],mid=(l+r)/2;
    if(s<k)       return kth(l,mid,lc[p],k-s);
    else if(s>=k) return kth(mid+1,r,rc[p],k);
}
int delRange(int l,int r,int &p,int tarl,int tarr){
    if(tarl<=l&&r<=tarr){
        int ans=tr[p];
        p=0;
        return ans; 
    }
    int mid=(l+r)/2,ans=0;
    if(mid>=tarl&&lc[p])  ans=delRange(l,mid,lc[p],tarl,tarr);
    if(mid<tarr&&rc[p])   ans+=delRange(mid+1,r,rc[p],tarl,tarr);
    tr[p]=tr[lc[p]]+tr[rc[p]];//ATTTTTTTTENTIONNNNNNNNNNNN!This sentence is REALLY INDISPENSABLE and esaily to forget!!!
    return ans;
}

int main()
{
    int dept=0,tot=0;
    cin>>n>>minn;
    minn+=N;
    for(int i=1;i<=n;i++){
        char x;int k;
        cin>>x>>k;
        if(x=='I'){
            if(k+N-delta>=minn){
                ins(1,2*N,root,k+N-delta);
                tot++;
            }
        }
        else if(x=='A'){
            minn-=k;delta+=k;
        }
        else if(x=='S'){
            minn+=k;delta-=k;
            if(minn>1)dept+=delRange(1,2*N,root,1,minn-1);
        }
        else if(x=='F'){
            if(k>tot-dept)  cout<<"-1"<<endl;
            else            cout<<(kth(1,2*N,root,k)-N+delta)<<endl;
        }
    }
    cout<<dept;
    return 0;
}