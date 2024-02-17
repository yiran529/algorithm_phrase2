#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class union_find{
    private:
        vector<int> id;
        int cnt=0;
        vector<int> size;
    public:
        union_find(int num){
            cnt=num;
            for(int i=0;i<num;i++){
                id.push_back(i);
                size.push_back(1);
            }
        }
        int count(){return cnt;}
        int find(int target){
            while(id[target]!=target)target=id[target];
            return target;
        }
        bool connected(int p,int q){
            int i=find(p);
            int j=find(q);
            return i==j;
        }
        void uni(int p,int q){
            int i=find(p);
            int j=find(q);
            if(i==j)return ;
            if(size[i]>size[j]){id[j]=i;size[i]+=size[j];}
            else               {id[i]=j;size[j]+=size[i];}
            cnt--;
        }
};
int main()
{
    int n,m;
    cin>>n>>m;
    union_find UF(n);
    for(int i=0;i<m;i++){
        int p,q;
        cin>>p>>q;
        UF.uni(p,q);
    }
    while(true){
        int p,q;
        cin>>p>>q;
        cout<<UF.connected(q,p);
    }
    return 0;
}