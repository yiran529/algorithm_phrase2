#include<iostream>
#include<algorithm>
#include<stack>
#include<math.h>
using namespace std;
int main()
{
    int n,heights[100000],ans=0,left[100000],right[100000];
    cin>>n;
    stack<int> stk;
    for(int i=0;i<n;i++)cin>>heights[i];
    for(int i=0;i<n;i++){
        while(!stk.empty()&&heights[stk.top()]>=heights[i])stk.pop();
        left[i]=(stk.empty()?-1:stk.top());
        stk.push(i);
    } 
    stk=stack<int>();
    for(int i=n-1;i>0;i--){
        while(!stk.empty()&&heights[stk.top()]>=heights[i])stk.pop();
        right[i]=(stk.empty()?n:stk.top());
        stk.push(i);
    } 
    for(int i=0;i<n;i++)ans=max(ans,heights[i]*(right[i]-left[i]-1));
    cout<<ans;
    return 0;
}