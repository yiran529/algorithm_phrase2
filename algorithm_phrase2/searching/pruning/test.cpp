#include<iostream>
#include<map>
using namespace std;
int main()
{
    map<int,pair<int,int>> mp;
    int x=3,u=2;
    mp[1]=make_pair(x,u);
    cout<<mp[1].first;
    return 0;
}