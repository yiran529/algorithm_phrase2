#include<iostream>
#include<climits>
#include<algorithm>
using namespace std;
int n,m,a[200],sum[200],dpmax[200][200][20],dpmin[200][200][20];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i+n]=a[i];
        sum[i]+=sum[i-1]+a[i];
    }
    for(int i=n+1;i<=2*n;i++)sum[i]=sum[i-1]+a[i];
    for(int l=1;l<=2*n;l++)
        for(int r=l;r<=2*n;r++){
            int s=(sum[r]-sum[l-1])%10;//注意是l-1
            if(s<0)s+=10;
            dpmax[l][r][1]=dpmin[l][r][1]=s;
        }
    for(int k=2;k<=m;k++){
        for(int l=1;l<=2*n-k+1;l++){
            //for(int r=l+k-1;r<=2*n-k+1&&r<=l+n-m+k-1;r++){
            for(int r=l+k-1;r<=2*n;r++){
                int maxx=INT_MIN,minn=INT_MAX;
                for(int i=l+k-2;i<r;i++){//注意是小于r
                    int s=(sum[r]-sum[i])%10;
                    if(s<0)s+=10;
                    int curmax=dpmax[l][i][k-1]*s;
                    int curmin=dpmin[l][i][k-1]*s;
                    maxx=(maxx>curmax?maxx:curmax);
                    minn=(minn<curmin?minn:curmin);
                }
                dpmax[l][r][k]=maxx;dpmin[l][r][k]=minn;
            }
        }
    }
    int ansmax=INT_MIN,ansmin=INT_MAX;int deb;
    for(int i=1;i<=n+1;i++){
        if(dpmax[i][i+n-1][m]>ansmax)ansmax=dpmax[i][i+n-1][m];
        if(dpmin[i][i+n-1][m]<ansmin)ansmin=dpmin[i][i+n-1][m];
    }
    cout<<ansmin<<endl<<ansmax;
    return 0;

}