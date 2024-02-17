#include<iostream>
#include<string.h>
#include<queue>
#define DAY 86400
using namespace std;
int main()
{
    queue<pair<int,int>> q;
    int n,nationality[100001],cnt=0;
    memset(nationality,0,100001*sizeof(int));
    cin>>n;
    for(int i=1;i<=n;i++){
        long t;int num,nat;
        cin>>t>>num;
        for(int j=1;j<=num;j++){
            cin>>nat;
            pair<int,int>passenger(t,nat);
            q.push(passenger);
            if(nationality[nat]==0)cnt++;
            nationality[nat]++;
        }
        while(t-q.front().first>=DAY){
            pair<int,int>passenger=q.front();
            q.pop();
            if(nationality[passenger.second]==1)cnt--;
            nationality[passenger.second]--;
        }
        cout<<cnt<<endl;
    }
    return 0;
}