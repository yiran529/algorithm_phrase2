#include<iostream>
#include<climits>
#include<algorithm>
#include<stdlib.h>
#define loop for(int i=1;i<=n;i++)
using namespace std;
int n,k,coord[51][2],maxx[51][51],minn[51][51],dp[51][51][10];
int cmp(const void *a,const void *b){
   int *x=(int*)a,*y=(int*)b;
   return x[0]-y[0]; 
}
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>coord[i][1]>>coord[i][0];
    qsort(coord+1,n,sizeof(coord[0]),cmp);
    for(int i=1;i<=n;i++){
        int curmax=coord[i][1],curmin=coord[i][1];
        for(int j=i;j<=n;j++){
            if(coord[j][1]>curmax)curmax=coord[j][1];
            if(coord[j][1]<curmin)curmin=coord[j][1];
            maxx[i][j]=curmax,minn[i][j]=curmin;
            dp[i][j][1]=(coord[j][0]-coord[i][0])*(maxx[i][j]-minn[i][j]);
        }
    }
    for(int part=2;part<=k;part++){
        for(int l=1;l<=n-part+1;l++){
            for(int r=l+part-1;r<=n;r++){
                dp[l][r][part]=INT_MAX;
                for(int i=l+part-2;i<r;i++){
                    int s=(coord[r][0]-coord[i+1][0])*(maxx[i+1][r]-minn[i+1][r]);
                    if(dp[l][i][part-1]+s<dp[l][r][part])dp[l][r][part]=dp[l][i][part-1]+s;
                }
            }
        }
    }
    cout<<dp[1][n][k];
    return 0;
}