#include<iostream>
#include<algorithm>
#include<map>
#include<cmath>
#define N 10000005
int cnt,tr[1000005*8],lc[1000005*8],rc[1000005*8],root;
using namespace std;
void ins(int l,int r,int tar,int &p,int sign){
    if(p==0)p=++cnt;
    tr[p]+=sign;
    if(l==r)return;//Do not forget this!相当于在平衡树中到达叶子节点要返回一样。
    int mid=l+(r-l>>1);
    if(mid<tar)ins(mid+1,r,tar,rc[p],sign);
    else       ins(l,mid,tar,lc[p],sign);
}
int rk(int l,int r,int tar,int p){
    int mid=l+(r-l>>1);
    if(mid+1<tar)       return tr[lc[p]]+rk(mid+1,r,tar,rc[p]);
    else if(mid+1==tar) return tr[lc[p]]+1;
    else                return rk(l,mid,tar,lc[p]);
}
// int queryx(int rt,int l,int r,int ql,int qr)
// {
//     int mid=(l+r)/2,ans=0;
//     if(ql<=l&&r<=qr)return tr[rt];
//     if(ql<=mid)ans+=queryx(lc[rt],l,mid,ql,qr);
//     if(qr>mid)ans+=queryx(rc[rt],mid+1,r,ql,qr);
//     return ans;
// }
int kth(int l,int r,int k,int p){
    if(l==r)return l;
    int mid=l+(r-l>>1);
    if(tr[lc[p]]>=k)return kth(l,mid,k,lc[p]);
    else            return kth(mid+1,r,k-tr[lc[p]],rc[p]);
}
int pre(int l,int r,int p,int k){

}
int main()
{
    map<int,int> mp;
    int n;scanf("%d",&n);
    for(int i=1; i<=n; i++){
        int op,x;
        cin>>op>>x;
        switch(op){
            case 1:ins(1,2*N,N+x,root,1),mp[x]++; break;//为什么要+N？因为x有可能是负数。
            case 2:ins(1,2*N,N+x,root,-1),mp[x]--;
                    if(mp[x]==0)mp.erase(x);break;
            case 3:printf("%d\n",rk(1,2*N,N+x,root));break;
            //case 3:printf("%d\n",queryx(root,1,N*2,1,x+N-1)+1);break;
            case 4:printf("%d\n",kth(1,2*N,x,root)-N);break;
            case 5:printf("%d\n",(--mp.lower_bound(x))->first);break;
            case 6:printf("%d\n",(mp.upper_bound(x))->first);break;
        }
    }
    return 0;
}