#include<iostream>
#include<utility>
#include<ctime>
#include<map>
using namespace std;
template<typename K,typename V>
class SplayTree{
    private://YOU MUST WRITE THIS!
    class NODE{
        public:
        K key;
        V val;
        NODE* pa;
        NODE* lchild;
        NODE* rchild;
        int cnt;
        NODE(K k,V v):key(k),val(v),cnt(1),pa(NULL),lchild(NULL),rchild(NULL){}
    };
    NODE* root=NULL;
    bool isLeftChild (NODE* cur){return (cur&&cur->pa&&cur==cur->pa->lchild);}
    bool isRightChild(NODE* cur){return (cur&&cur->pa&&cur==cur->pa->rchild);}
    NODE* rotateLeft(NODE* cur){
        NODE* save=cur->rchild,*f=cur->pa;
        cur->rchild=save->lchild;
        if(save->lchild)save->lchild->pa=cur;
        save->lchild=cur;
        if(f==NULL)root=save;
        else{
            if(isLeftChild(cur))f->lchild=save;
            else                f->rchild=save;
        }
        save->pa=f;
        cur->pa=save;
        return save;
    }
    NODE* rotateRight(NODE* cur){
        NODE* save=cur->lchild,*f=cur->pa;
        cur->lchild=save->rchild;
        if(save->rchild)save->rchild->pa=cur;
        save->rchild=cur;
        if(f==NULL)root=save;
        else{
            if(isLeftChild(cur))f->lchild=save;
            else                f->rchild=save;
        }
        save->pa=f;
        cur->pa=save;
        return save;
    }
    void splay(NODE* cur){//tar indicates where SPLAY stop
        //6 cases
        while(cur!=root){
            if(cur->pa==root){
                
                if(isLeftChild(cur))rotateRight(root);
                else                rotateLeft (root);
            }
            else{
                //cout<<isLeftChild(cur)<<cur->pa->pa->key;
                if     (isLeftChild(cur) && isLeftChild(cur->pa)){
                    rotateRight(cur->pa->pa);
                    rotateRight(cur->pa);
                }
                else if(isRightChild(cur)&&isRightChild(cur->pa)){
                    rotateLeft(cur->pa->pa);
                    rotateLeft(cur->pa);
                }
                else if(isRightChild(cur) &&isLeftChild(cur->pa)){
                    rotateLeft(cur->pa);
                    rotateRight(cur->pa);
                }
                else if(isLeftChild(cur) &&isRightChild(cur->pa)){
                    rotateRight(cur->pa);
                    rotateLeft(cur->pa);
                }
            }
        }
    }
    SplayTree(NODE* r):root(r){}
    NODE* findMax(NODE* cur){
        if(cur->rchild==NULL)return cur;
        else return findMax(cur->rchild);
    }
    NODE* join(NODE *x,NODE *y){//ASSUME that a all keys in are less than those in y
        if(x==NULL)return y;else if(y==NULL)return x;
        else{
            x->pa=NULL;
            SplayTree<K,V>* a=new SplayTree(x);
            SplayTree<K,V>* b=new SplayTree(y);
            a->splay(a->findMax(x));
            a->root->rchild=y;
            a->root->pa=NULL;
            a->root->rchild->pa=a->root;
            return a->root;
        }
    }    
    NODE* find(NODE* cur,K k){
        if(cur==NULL)return NULL;
        if(cur->key==k){splay(cur);return cur;}
        else if(cur->key<k){
            if(cur->rchild)return find(cur->rchild,k);
            else {splay(cur);return NULL;}
        }
        else {
            if(cur->lchild)return find(cur->lchild,k);
            else {splay(cur);return NULL;}
        }
    }
    public:
    void print(NODE* cur,int indentNum){
        if(cur==NULL)return;
        for(int i=1;i<=indentNum;i++)cout<<" ";
        cout<<cur->key<<"|"<<cur->val<<"|"<<(cur->pa?cur->pa->key:0)<<endl;
        print(cur->lchild,indentNum+2);
        print(cur->rchild,indentNum+2);
    }
    SplayTree(){}
    void insert(const K &k,const V &v){
        NODE* cur=root;
        if(root==NULL){
            root=new NODE(k,v);
            return;
        }
        while(1){
            if(cur->key==k){
                cur->cnt++;
                splay(cur);
                break;
            }
            if     (cur->key<k&&cur->rchild)cur=cur->rchild;
            else if(cur->key>k&&cur->lchild)cur=cur->lchild;
            else if(cur->key<k){
                cur->rchild=new NODE(k,v);
                cur->rchild->pa=cur;
                splay(cur->rchild);
                break;
            }
            else if(cur->key>k){
                cur->lchild=new NODE(k,v);
                cur->lchild->pa=cur;
                splay(cur->lchild);
                break;
            }
        }
    }
    void remove(const K &k){
        NODE* tar=find(root,k);//"find" includes the splay operation
        if(tar==NULL)return;
        NODE* save=root;
        root=join(root->lchild,root->rchild);
        root->pa=NULL;
        delete save;
    }
    V& find(const K &k){
        NODE* tar=find(root,k);
        if(tar==NULL){cout<<"Error!";return root->val;}
        return tar->val; 
    }
    void print(){print(root,0);}
};
int main()
{
    srand(time(0));
    SplayTree<int,int> spt;
    int opNum;
    clock_t s=clock();
    for(int i=1;i<=1000000;i++){
        int option,x,y;
        option=rand()%2,x=rand()%10000,y=rand()%10000;
        if(option==1)spt.insert(x,y);
        else if(option==2)spt.remove(x);
        else if(option==3)cout<<spt.find(x);
    }
    clock_t e=clock();
    cout<<e-s;//DAMN!!!SO FAST!
    map<int,int> mp;
    s=clock();
    for(int i=1;i<=1000000;i++){
        int option,x,y;
        option=rand()%2,x=rand()%10000,y=rand()%10000;
        if(option==1)mp[x]=y;
        else if(option==2)mp.erase(x);
        else if(option==3)cout<<spt.find(x);
    }
    e=clock();
    cout<<e-s;
    return 0;
}