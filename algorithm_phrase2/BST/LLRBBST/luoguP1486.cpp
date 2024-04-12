#include<iostream>
#include<cstdio>
#include<cmath>
#define red 1
#define black 2
using namespace std;
int n,minn;
struct NODE{//We use LLRBT
    int salary,l,r,size,color;
}node[100001];
bool inTree[100001];
int root;
void flipColors(int cur){
    if(node[cur].color==red){
        node[cur].color=black;
        if(inTree[node[cur].l])node[node[cur].l].color=red;
        if (inTree[node[cur].r])node[node[cur].r].color=red;
    }
    else if(node[cur].color==black){
        node[cur].color=red;
        if(inTree[node[cur].l])node[node[cur].l].color=black;
        if (inTree[node[cur].r])node[node[cur].r].color=black;
    }
}
void updateSize(int cur){
    int lsize=0,rsize=0;
    if(inTree[node[cur].l])lsize=node[node[cur].l].size;
    if(inTree[node[cur].r])rsize=node[node[cur].r].size;
    node[cur].size=lsize+1+rsize;
}
int minNode(int cur){
    if(inTree[node[cur].l]==false)return cur;
    else return minNode(node[cur].l);
}
int leftRotate(int cur){
    int save=node[cur].r;
    node[cur].r=node[save].l;
    node[save].l=cur;
    if(root==cur)root=save;
    updateSize(cur),updateSize(save);//Do not forget
    int c=node[cur].color;
    node[cur].color=node[save].color;
    node[save].color=c;//Do not forget
    return save;
}
int rightRotate(int cur){
    int save=node[cur].l;
    node[cur].l=node[save].r;
    node[save].r=cur;
    if(root=cur)root=save;
    updateSize(cur),updateSize(save);
    int c=node[cur].color;
    node[cur].color=node[save].color;
    node[save].color=c;
    return save;
}
bool isRed(int cur){
    return (inTree[cur]&&node[cur].color==red);
}
int fixBalance(int cur){
    if( isRed(node[cur].r) )cur=leftRotate(cur);
    if( isRed(node[cur].l) && isRed(node[node[cur].l].l) )cur=rightRotate(cur);
    if( isRed(node[cur].l) && isRed(node[cur].r))flipColors(cur);
    return cur;
}
int insert(int cur,int newNode){//newNode的初始化在驱动函数已经完成
    if(inTree[cur]==false)return newNode;
    else if(node[cur].salary>node[newNode].salary)
        node[cur].l=insert(node[cur].l,newNode);
    else node[cur].r=insert(node[cur].r,newNode);
    updateSize(cur);//Do not forget about this!
    return fixBalance(cur);
}
void insert(int newNode,int salary,int SIGN){//SIGN用来区分驱动例程和真正的插入函数
    node[newNode].salary=salary;
    node[newNode].color=red;
    node[newNode].size=1;
    node[newNode].l=node[newNode].r=0;//0表示空节点
    inTree[newNode]=true;
    if(SIGN==true){root=newNode;node[newNode].color=black;}
    else insert(root,newNode);
} 
int remove(int cur,int newNode){
    if(cur==0)return cur;
    if(node[cur].salary>node[newNode].salary){
        if(!isRed(node[cur].l)&&!isRed(node[node[cur].l].l)){
            flipColors(cur);
            if( isRed(node[node[cur].r].l) ){//Remember this!
                node[cur].r=rightRotate(node[cur].r);
                cur=leftRotate(cur);
                flipColors(cur);
            }
        }
        node[cur].l=remove(node[cur].l,newNode);
    }
    else if(node[cur].salary<node[newNode].salary){
        if(isRed(node[cur].l))cur=rightRotate(cur);
        if(!isRed(node[cur].r)&&!isRed(node[node[cur].r].l)){//别忘记第二个条件！！！！！
            flipColors(cur);
            if(isRed(node[node[cur].l].l)){
                cur=rightRotate(cur);
                flipColors(cur);
            }
        }
        node[cur].r=remove(node[cur].r,newNode);
    }
    else if(node[cur].salary==node[newNode].salary){
        if(!inTree[node[cur].r]&&!inTree[node[cur].l]){inTree[newNode]=false;return 0;}
        if(!inTree[node[cur].r]){
            inTree[cur]=false;
            if(node[cur].color==black)node[node[cur].l].color=black;
            else                      node[node[cur].l].color=red;
            return node[cur].l;
        }
        else if(!inTree[node[cur].l]){
            inTree[cur]=true;
            if(node[cur].color==black)node[node[cur].r].color=black;
            else                      node[node[cur].r].color=red;
            return node[cur].r;
        }
        else {
            int m=minNode(node[cur].r);
            node[cur].salary=node[m].salary;
            node[cur].r=remove(node[cur].r,m);
        }
    }
    updateSize(cur);
    return fixBalance(cur);
}
void remove(int target){
    inTree[target]=false;
    node[root].color=red;
    remove(root,target);
    node[root].color=black;
    if(inTree[root]==false)root=0;///////
}
int rankk(int cur,int k){
    if(node[node[cur].r].size+1==k)return cur;
    if(node[node[cur].r].size+1< k)return rankk(node[cur].l,k-node[node[cur].r].size-1);
    return rankk(node[cur].r,k);
}
int main()
{
    cin>>n>>minn;
    int delta=0;
    inTree[0]=false;//IMPORTANT!
    node[0].size=0;//IMPORTANT!
    node[0].color=black;
    int nodeNum=0;
    int deltaRec[100001];
    root=0;
    int removeNum=0;
    for(int i=1;i<=n;i++){
        char choice;int x;
        cin>>choice>>x;
        switch(choice){
            case 'I':{
                nodeNum++;
                deltaRec[nodeNum]=delta;
                bool SIGN=(root==0?true:false);
                if(x-delta>=minn)insert(nodeNum,x-delta,SIGN);
                break;
            }
            case 'A':{delta+=x;minn-=x;break;}//Notice this special trick
            case 'S':{
                delta-=x;minn+=x;
                int m;
                while(node[minNode(root)].salary<minn){remove(minNode(root));removeNum++;}
                break;
            }
            case 'F':{
                if(x>node[root].size)cout<<"-1"<<endl;
                else {
                    int t=rankk(root,x);
                    cout<<node[t].salary+delta<<endl;
                }
                break;
            }
        }
    }
    cout<<node[node[root].r].salary<<endl;
    cout<<removeNum;
    return 0;
}
//qwq全戳。。。懒得改了。。。