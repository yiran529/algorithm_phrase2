#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<climits>
#include<ctime>
#include<algorithm>
using namespace std;
class TREAP{
    private:
        class NODE{
            public:
                int key;
                int size;
                int cnt=0;
                int priority;
                NODE* r;
                NODE* l;
                NODE():size(0){}
                NODE(int k):key(k),size(1),cnt(1),l(NULL),r(NULL){
                    priority=rand()*rand()%19620817;
                }
                void updateSize(){
                    size=cnt;
                    if(r!=NULL)size+=r->size;
                    if(l!=NULL)size+=l->size;
                }
        };
        NODE* root;
        NODE* rotateLeft(NODE *h);
        NODE* rotateRight(NODE *h);
        NODE* insert(NODE* h,int k);
        NODE* fixup(NODE* h);
        void print(NODE* h,int depth);
        void mdel(NODE* h){
            if(h==NULL)return;
            if(h->r)mdel(h->r);
            if(h->l)mdel(h->l);
            delete h;
        }
        NODE* dele(NODE*h,int k);
        int rank(NODE* h,int k);
        int get_key(NODE* h,int rank);
    public:
        TREAP(int first_k):root(new NODE(first_k)){}
        void insert(int k){insert(root,k);};
        void print(){print(root,0);}
        ~TREAP(){mdel(root->r);mdel(root->l);}
        void dele(int k){dele(root,k);}
        int rank(int k){return rank(root,k)+1;}
        int get_key(int rank){return get_key(root,rank);}
        int pro(int k){return get_key(rank(k)-1);}
        int succ(int k){return get_key(rank(k+1));}
};
TREAP::NODE* TREAP::rotateLeft(NODE *h){
    NODE* save=h->r;
    h->r=save->l;
    save->l=h;
    if(h==root)root=save;
    save->updateSize(),h->updateSize();
    return save;
}
TREAP::NODE* TREAP::rotateRight(NODE *h){
    NODE* save=h->l;
    h->l=save->r;
    save->r=h;
    if(h==root)root=save;
    save->updateSize(),h->updateSize();
    return save;
}
TREAP::NODE* TREAP::fixup(NODE* h){
    if(h->l!=NULL && h->priority>h->l->priority)h=rotateRight(h);
    else if(h->r!=NULL && h->priority>h->r->priority)h=rotateLeft(h);
    h->updateSize();
    if(h->l)h->l->updateSize();
    if(h->r)h->r->updateSize();
    return h;
}
TREAP::NODE* TREAP::insert(NODE *h,int k){
    if (h==NULL){return new NODE(k);}
    else if(h->key==k){h->size++;h->cnt++;}
    else if(h->key<k)h->r=insert(h->r,k);
    else if(h->key>k)h->l=insert(h->l,k);
    return fixup(h);
}
TREAP::NODE* TREAP::dele(NODE *h,int k){
    if(k<h->key)h->l=dele(h->l,k);
    else if(k>h->key)h->r=dele(h->r,k);
    else if(k==h->key){
        if(h->cnt>1){h->cnt--;h->size--;return h;}
        else if(h->l==NULL && h->r==NULL){
            delete h;
            return NULL;
        }
        else if(h->l==NULL){
            NODE* save=h->r;
            delete h;
            return save;
        }
        else if(h->r==NULL){
            NODE* save=h->l;
            delete h;
            return save;
        }
        else{
            if(h->l->priority<h->r->priority){
                h=rotateRight(h);
                h->r=dele(h->r,k);
            }
            else{
                h=rotateLeft(h);
                h->l=dele(h->l,k);
            }
        }
    }
    h->updateSize();
    return h;
}
void TREAP::print(NODE *h,int depth){
    if(h==NULL)return;
    int indent=depth*2;
    for(int i=0;i<indent;i++)cout<<" ";
    cout<<h->key<<'|'<<h->priority<<'|'<<h->size<<'|'<<h->cnt<<endl;
    print(h->l,depth+1),print(h->r,depth+1);
}
int TREAP::rank(NODE* h,int k){
    if (h==NULL)return 0;
    else if(h->key>=k)return rank(h->l,k);
    else return (h->l?h->l->size:0)+1+rank(h->r,k);
}
int TREAP::get_key(NODE* h,int rank){//有rank-1个数比它小
    if(h==NULL)return INT_MAX;
    else if(h->l && h->l->size>=rank)return get_key(h->l,rank);
    else if((h->l?h->l->size:0)+h->cnt>=rank)return h->key;
    else return get_key(h->r,rank-h->cnt-(h->l?h->l->size:0));
}
int main()
{
    srand(static_cast<unsigned int>(time(0)));
    int n,x,choice;
    cin>>n>>choice>>x;
    TREAP treap=TREAP(x);
    for (int i=1;i<n;i++){
        cin>>choice>>x;
        switch(choice){
            case 1:treap.insert(x);break;
            case 2:treap.dele(x);break;
            case 3:cout<<treap.rank(x)<<endl;break;
            case 4:cout<<treap.get_key(x)<<endl;break;
            case 5:cout<<treap.pro(x)<<endl;break;
            case 6:cout<<treap.succ(x)<<endl;break;
            default:break;
        }
    }
    return 0;
}