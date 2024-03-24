#include<cstdio>
#include<cmath>
#include<algorithm>
int main()
{
    int n;scanf("%d",&n);
    int power[203];
    for(int i=1;i<=n;i++)scanf("%d",&power[i]);
    for(int i=n+1;i<=n*2;i++)power[i]=power[i-n];//原问题是环状的，这里将其转换为链状
    long long ans=0,dp[203][203];
    for(int len=1;len<=n+1;len++){//必须从1开始，这样才可以处理到一些基本情况
        for(int i=1;i<=2*n-len+1;i++){
            dp[i][i+len-1]=0;
            for(int k=i+1;k<i+len-1;k++){
                dp[i][i+len-1]=fmax(dp[i][i+len-1],dp[i][k]+dp[k][i+len-1]
                                    +power[i]*power[k]*power[i+len-1]);
            }
        }
    }
    for(int i=1;i<=n;i++)ans=fmax(ans,dp[i][i+n]);
    printf("%lld",ans);
    return 0;
}