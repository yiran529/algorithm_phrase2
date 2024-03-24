#include<cstdio>
#include<algorithm>
#include<cmath>
#include<climits>
#include<iostream>
#define N 6005
/*这道题涉及一种特殊的树结构，即每个节点可能由多于两个的节点，这时我们用
一种特殊的方法表示这种树：每个节点的“左指针”指向最左边的子节点，“右指针”
指向它的右边邻近的兄弟节点*/
int n,happy[N];
struct NODE{
    int num;
    struct NODE* l;
    struct NODE* r;
}node[N];
short boss[N];
int dp[N][2];/*相应编号为最大上司且他可以去或不去时的最大快乐值,dp[][0]表示最大上司
不去，dp[][1]表示最大上司去*/
void solve(int num){
    if (node[num].l==NULL){//base case
        dp[num][0]=0;
        dp[num][1]=happy[num];  
        return;
    } 
    if (dp[num][0]>INT_MIN)return;//记忆化搜索
    dp[num][0]=0;dp[num][1]=happy[num];
    struct NODE* p=node[num].l;
    while(p){
        solve(p->num);
        dp[num][0]+=fmax(dp[p->num][0],dp[p->num][1]);//num不去，他的直接下属可去可不去
        dp[num][1]+=dp[p->num][0];//num去，这样num的直接下属就不能去
        p=p->r;
    }
}
int main()
{
    scanf("%d",&n);
    int i;
    for(i=1;i<=n;i++){
        scanf("%d",&happy[i]);
        node[i].num=i;
        node[i].l=node[i].r=NULL;
        dp[i][0]=dp[i][1]=INT_MIN;
    }
    for(i=1;i<=n-1;i++){
        int k,l;
        scanf("%d%d",&l,&k);
        if(node[k].l==NULL)node[k].l=&node[l];
        else {
            struct NODE* p=node[k].l;
            while(p->r)p=p->r;
            p->r=&node[l];
        }
        boss[l]=1;
    }
    for(i=1;i<=n;i++)if(boss[i]==0)break;
    solve(i);
    // std::cout<<std::endl;
    // for(i=1;i<=n;i++)std::cout<<dp[i][0]<<" "<<i<<std::endl;
    // std::cout<<std::endl;
    printf("%d",(int)fmax(dp[i][0],dp[i][1]));
    return 0;
}
///HOOOOOORAYYYYYYYY!I made it at the first shot!