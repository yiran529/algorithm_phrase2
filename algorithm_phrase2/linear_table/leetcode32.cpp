#include<iostream>
#include<stack>
#include<algorithm>
#include<string.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    stack<pair<char,int>> stc;
    char last_char;
    int nest_cnt=0, last_legal_close,para_len[300001];
    memset(para_len,-1,s.size()*sizeof(int));
    for(int i=0;i<s.size();i++){
        if(s[i]=='('){
            if(last_char!='('){
                
            }
            stc.push(make_pair('(',i));
        }
        else if((stc.size()==0||stc.top().first==')')&&s[i]==')'){
            stc.push(make_pair(')',i)); 
            para_len[i]=0;
        }
        else if(s[i]==')'){
            stc.pop();
            if(stc.size()==0||stc.top().first==')'){
                para_len[last_legal_close]=nest_cnt;
                nest_cnt=0;
            }
            else{
                nest_cnt+=2;
                last_legal_close=i;
            }
        }
        last_char=s[i];
    return 0;
}