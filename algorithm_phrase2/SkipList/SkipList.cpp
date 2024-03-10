#include<iostream>
#include<map>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<limits.h> 
template<typename K,typename V>
class SkipList
{
    private:
    class NODE{
        public:
        K key;
        V val;
        int level;
        NODE **forward;
        NODE(K k,V v,int l,NODE* next=NULL):key(k),val(v){
            forward = new NODE* [l+1];//ensure that no space is wasted
            level=l;
            for(int i=0;i<=l;i++)forward[i]=next;
        }
        ~NODE(){if (forward!=NULL)delete[] forward;}
    };
    int randLevel(){
        int l=1;
        while((rand()&S)<SP&&l<MaxLevel)l++;//位运算效率高
        return l;
    }
    const int INVALID=INT_MAX;
    const int MaxLevel=32;
    const int S=0xffff;
    const int P=4;
    const int SP=S/P;
    NODE *head,*tail;
    int length;
    int level;

    public:
    
    SkipList(){
        srand(time(0));
        level=length=0;
        tail=new NODE(INVALID,0,0);
        head=new NODE(INVALID,0,MaxLevel,tail);//head的高度为Max，保证在超过最高高度之前head都能发挥作用
    }
    ~SkipList(){delete tail;delete head;}
    void insert(const K &key,const V &val){
        NODE* update[MaxLevel+1];//不能用Level+1，因为可能在第六十二行爆掉
        NODE* p=head;
        for(int i=level;i>=0;i--){//The lowest level is 0!
            while(key>p->forward[i]->key)p=p->forward[i];//保证能在tail之前停下来
            update[i]=p;
        }
        p=p->forward[0];//Do not forget this!
        if(p->key==key){
            p->val=val;
            return;
        }
        int lv=randLevel();
        if(lv>level){//DO NOT FORGET THIS!
            lv=++level;
            update[lv]=head;
        }
        NODE *newNode=new NODE(key,val,lv);
        for(int i=0;i<=lv;i++){
            p=update[i];
            newNode->forward[i]=p->forward[i];
            p->forward[i]=newNode;
        }
        length++;
    }
    V &find(const K &key){
        NODE* p=head;
        for(int i=level;i>=0;i--){
            while(key>p->forward[i]->key)p=p->forward[i];
        }
        p=p->forward[0];
        if(p->key==key)return p->val;
        else return tail->val;
    }
    bool remove(const K &key){
        NODE* update[MaxLevel+1];
        NODE* p=head;
        for(int i=level;i>=0;i--){
            while(key>p->forward[i]->key)p=p->forward[i];
            update[i]=p;
        }
        p=p->forward[0];
        if(p->key!=key) return false;
        
        for(int i=0;i<=p->level;i++){
            update[i]->forward[i]=p->forward[i];
        }
        delete p;
        while(level>0&&head->forward[level]==tail)--level;//Do not forget to maintain 'level' and 'length'
        length--;
        return true;
    }
    int Size(){return length;}
    V& operator[](const K &k){
        V v=find(k);
        if(v==tail->val)insert(k,0);
        return find(k);
    }
    void printAll(){
        NODE* p=head->forward[0];
        while(p){
            std::cout<<p->key<<" ";
            p=p->forward[0];
        }
    }
};
int main()
{
    SkipList<int,int> sl;
    std::map<int,int> m; 
    clock_t s=clock();
    for(int i=0;i<100000;i++){
        int key=rand(),val=rand();
        sl[key]=val;
    }
    for(int i=0;i<100000;i++){
        int key=rand();
        if(i&1)sl.remove(key);
    }
    clock_t e=clock();
    std::cout<<"Performance of SkipList:"<<(double)(e-s)<<std::endl;
    s=clock();
    for(int i=0;i<1e5;i++){
        int key=rand(),val=rand();
        m[key]=val;
    }
    for(int i=0;i<1e5;i++){
        int key=rand();
        if(i&1)m.erase(key);
    }
    e=clock();
    std::cout<<"Performance of built-in map:"<<(double)(e-s)<<std::endl;
    return 0;
}