#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 500003
using namespace std;
struct TRIE{
    int bNum, num,next,right,end;/*分别表示该节点存储的二进制数01，
    在该节点下共有几个前缀，该节点匹配后在一维数组中的位置与不匹配节点在以为数组中的位置，
    以及有多少条信息在这个点结束。*/
}trie[N];
int newNode;

/*接受上一个父节点和一个二进制数为参数，
输出该二进制数最终插入（或不插入时）最终所在位置*/
void createNode(int y){
        newNode++;
        trie[newNode].bNum=y;
        trie[newNode].next=trie[newNode].right=0;
        trie[newNode].num=1;
        trie[newNode].end=0;
}
int insert(int pa,int y){
    int cur=trie[pa].next;
    if(cur==0){//空节点
        createNode(y);
        trie[pa].next=newNode;
        return newNode;
    }
    //非空节点
    if(trie[cur].bNum==y){
        trie[cur].num++;
        return cur;
    }
    else{
        int save=cur;
        cur=trie[cur].right;
        if(cur!=0){trie[cur].num++;return cur;}
        else{
            createNode(y);
            trie[save].right=newNode;
            return newNode;
        }
    }
}

int main()
{
    int m,n;
    cin>>m>>n;
    trie[0].next=trie[0].right=trie[0].num=0;
    trie[0].bNum=2;
    for(int i=1;i<=m;i++){
        int x;cin>>x;
        int pa=0;
        for(int j=1;j<=x;j++){
            int y;cin>>y;
            pa=insert(pa,y);
        }
        trie[pa].end++;
    }    
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        int pa=1,save=0,ans=0;
        for(int j=1;j<=x;j++){
            int y;cin>>y;
            if     (j<x&&(trie[pa].bNum==y||trie[pa].bNum!=y&&trie[pa].right!=0)){
                if(trie[pa].bNum!=y)pa=trie[pa].right;
                ans+=trie[pa].end;
                pa=trie[pa].next;
            }
            else if(j==x&&(trie[pa].bNum==y||trie[pa].bNum!=y&&trie[pa].right!=0)){
                if(trie[pa].bNum!=y)pa=trie[pa].right;
                ans+=trie[pa].num;
                pa=0;
            }
            else pa=0;///easily forget
        }
        cout<<ans<<endl;
    }

    return 0;
}