#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define N 100020
using namespace std;
struct NODE{
    int l,r;
    ll sum,lazyTag;
}node[N];
ll ele[N];
int n,m,i;
void build(int l,int r,int p){
    if(l==r){
        node[p].sum=ele[l];
        node[p].l=node[p].r=l;
        return;
    }
    int mid=l+((r-l)>>1);//移位运算优先级小于加！
    build(l,mid,2*p);
    build(mid+1,r,2*p+1);
    node[p].sum=node[2*p].sum+node[2*p+1].sum;
    node[p].l=l,node[p].r=r;
}
ll getSum(int l,int r,int tarl,int tarr,int p){/*将一个标记传给子节点时
            立即将相应的标记的值加到子节点的sum上，也就是说，只要一个节点带有标记，
            那么这个节点的sum就是已经更新过的了，这样的约定便于后续处理*/
    if(l>=tarl&&r<=tarr)return node[p].sum;
    int mid=l+((r-l)>>1);
    if(node[p].lazyTag){
        node[2*p].sum+=node[p].lazyTag*(node[2*p].r-node[2*p].l+1);
        node[2*p].lazyTag+=node[p].lazyTag;//是+=，不是=，因为要考虑原来就已经有标记的情况
        node[2*p+1].sum+=node[p].lazyTag*(node[2*p+1].r-node[2*p+1].l+1);
        node[2*p+1].lazyTag+=node[p].lazyTag;
        node[p].lazyTag=0;
    }
    ll sum=0;
    if(mid+1<=tarr)sum =getSum(mid+1,r,tarl,tarr,2*p+1);
    if(mid>=tarl)  sum+=getSum(l,mid,tarl,tarr,2*p);//切勿忘记这两个判断！！！！
    return sum;
}
void update(int l,int r,int tarl,int tarr,int p,int delta){
    if(l>=tarl&&r<=tarr){
        node[p].sum+=(r-l+1)*delta;
        node[p].lazyTag+=delta;
        return;
    }
    if(node[p].lazyTag){//不要忘记这个。每次访问带标记的节点都要进行修改！
        node[2*p].sum+=node[p].lazyTag*(node[2*p].r-node[2*p].l+1);
        node[2*p].lazyTag+=node[p].lazyTag;//是+=，不是=，因为要考虑原来就已经有标记的情况
        node[2*p+1].sum+=node[p].lazyTag*(node[2*p+1].r-node[2*p+1].l+1);
        node[2*p+1].lazyTag+=node[p].lazyTag;
        node[p].lazyTag=0;
    }
    int mid=l+((r-l)>>1);
    if(mid+1<=tarr)update(mid+1,r,tarl,tarr,2*p+1,delta);
    if(mid>=tarl)  update(l,mid,tarl,tarr,2*p,delta);
    node[p].sum=node[2*p].sum+node[2*p+1].sum;//容易忘记这个。不能直接用区间长度乘delta加上到p！
}   
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)cin>>ele[i];
    build(1,n,1);
    for(i=1;i<=m;i++){
        int choice,x,y;
        cin>>choice>>x>>y;
        if(choice==1){
            ll delta;cin>>delta;
            update(1,n,x,y,1,delta);
        }
        else cout<<getSum(1,n,x,y,1)<<endl;
    }
    return 0;
}
