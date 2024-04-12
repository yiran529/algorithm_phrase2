#include<iostream>
#include<climits>
#include<algorithm>
#include<cmath>
using namespace std;
long long tree[200005];
int t,d,m;
void add(int tar,int data,int p,int l,int r){
    if(l==r){
        tree[p]=data;//也即l=r=tar
        return;
    }
    int mid=(l+r)/2;
    if(mid<tar)add(tar,data,2*p+1,mid+1,r);
    else       add(tar,data,2*p,l,mid);
    tree[p]=fmax(tree[2*p],tree[2*p+1]);
}
long long query(int l,int r,int p,int curl,int curr){
    if(curl>=l&&curr<=r)return tree[p];
    int mid=(curr+curl)/2;
    long long maxx=LONG_LONG_MIN;
    if(mid>=l)  maxx=fmax(maxx,query(l,r,2*p,curl,mid));
    if(mid+1<=r)maxx=fmax(maxx,query(l,r,2*p+1,mid+1,curr));
    return maxx;  
}
int main()
{
    int tot=0;
    cin>>m>>d;
    for(int i=1;i<=m;i++){
       char op;int x;
       cin>>op>>x; 
       switch(op){
            case 'A':{
                add(++tot,(x+t)%d,1,1,m);
                break;
            }
            case 'Q':{
                if(x==0)t=0;
                else t=query(tot-x+1,tot,1,1,m);
                cout<<t;
                break;
            }
       }
    }
    return 0;
}