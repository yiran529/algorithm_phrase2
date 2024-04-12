#include<iostream>
#include<stack>
using namespace std;
#define N 500005
int h[N],r[N];
int main()
{
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        r[i]=1;
    }
    stack<int> st;
    long long ans=0;
    for(int i=1;i<=n;i++){
        while(!st.empty()&&h[st.top()]<=h[i]){
            ans+=r[st.top()];
            if(h[st.top()]==h[i])r[i]+=r[st.top()];
            st.pop();
        }
        if(!st.empty())ans+=1;
        st.push(i);
    }
    cout<<ans;
    return 0;
} 
