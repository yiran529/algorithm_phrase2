#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#define N 1000003
struct TREE{
    int root;
    int l;//这棵树表示的区间段的最左端的编号
    int r;
    long long val;
    int size;
}pack[N];//不是记录对应编号的节点，而是存储一个队列，队列每个元素是一棵左偏树的代表元素
int child[N][2],dis[N];
long long a[N],b[N];
int merge(int x,int y){//返回合并后的树的根节点在a序列中对应的编号
    if(x==0)return y;
    else if(y==0)return y;
    if(a[x]>a[y])return merge(y,x);
    child[x][1]=merge(child[x][1],y);
    if(dis[child[x][1]]>dis[child[x][0]]){
        int t=child[x][1];
        child[x][0]=child[x][1];
        child[x][1]=t;
    }
    dis[x]=dis[child[x][1]]+1;
    return x;
}
int n;

int main()
{
    int n;scanf("%d",&n);
    dis[0]=-1;
    for (int i=1;i<=n;i++){
        scanf("%lld",&a[i]);a[i]-=i;
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        pack[++cnt]=(TREE){i,i,i,a[i],1};
        while(cnt>1&&pack[cnt-1].val>pack[cnt].val){
            --cnt;
            pack[cnt].root=merge(pack[cnt].root,pack[cnt+1].root);
            pack[cnt].size+=pack[cnt+1].size;
            while(pack[cnt].size*2>pack[cnt].r-pack[cnt].l+2){
                pack[cnt].size--;
                pack[cnt].root=merge(child[pack[cnt].root][0],child[pack[cnt].root][1]);
            }
            pack[cnt].val=a[pack[cnt].root];
        }
    }
    long long ans=0;
    for(int i=1;i<=cnt;i++){
        for(int j=pack[i].l;j<=pack[i].r;j++){
            b[j]=pack[i].val;
            ans+=abs(a[j]-b[j]);
        }
    }
    printf("%lld\n",ans);
    for(int i=1;i<=n;i++)printf("%lld ",b[i]+i);
    return 0;
}