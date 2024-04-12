#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int t,d,m;
int main()
{
    int tot=0;
    int st[200005][20];
    cin>>m>>d;
    for(int i=1;i<=m;i++){
       char op;int x;
       cin>>op>>x; 
       switch(op){
            case 'Q':{
                int l=tot-x,r=tot-1;
                int gap=floor(log(r-l+1)/log(2));
                t=fmax(st[l][gap],st[r-(int)pow(2,gap)+1][gap]);
                cout<<t<<endl;
                break;
            }
            case 'A':{
                x=(x+t)%d;
                if(tot==0){st[0][0]=x;tot++;}
                else{
                    tot++;
                    int gap=floor(log(tot)/log(2));
                    st[tot-1][0]=x;
                    for(int i=1;i<=gap;i++)
                        st[tot-1-(int)pow(2,i)+1][i]=fmax(st[tot-1-(int)pow(2,i)+1][i-1],st[tot-1-(int)pow(2,i-1)+1][i-1]);//The key
                }
                break;
            }
       }
    }
    return 0;
}