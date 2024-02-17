#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct TST{
    char c;
    struct TST* left;//ASCII小于c
    struct TST* middle;//等于
    struct TST* right;//大于
    int val;
}tst;
tst* root=NULL;

void input();
void search_propel();//搜索驱动例程
void put(char* s,int value);
int search(char* s);//返回value值

int main()
{
    input();
    search_propel();
    return 0;
}
void input()
{
    int n,i; char s[100][100];
    scanf("%d",&n);
    for(i=1;i<=n;i++){scanf("%s",s[i]);put(s[i],i);}
}
void put(char* s,int value)
{
    if(root==NULL){
       root=(tst*)malloc(sizeof(tst));
       root->c=s[0];
       root->right=root->left=root->middle=NULL;
    }
    tst* p=root,*last;
    int i=0;char direction;//direction用以保存上一次比较后去的是last的哪个孩子节点
    while(p!=NULL&&i<strlen(s)){
        last=p;//用以保存路径上p的上一个结点
        if(s[i]==p->c){
            i++;
            p=p->middle;
            direction=2;
        }
        else if(s[i]<p->c){p=p->left;direction=1;}
        else if(s[i]>p->c){p=p->right;direction=3;}//这里不要i++
    }
    tst* p2;
    if(p==NULL&&i<strlen(s)){//原来TST中没有这个单词
        p2=(tst*)malloc(sizeof(tst));
        p2->left=p2->right=p2->middle=NULL;
        if(direction==1)last->left=p2;
        else if(direction==2)last->middle=p2;
        else last->right=p2;
        for(;i<strlen(s);i++){
            p2->c=s[i];
            if(i<strlen(s)-1){
                p2->middle=(tst*)malloc(sizeof(tst));
                p2=p2->middle;
                p2->left=p2->right=p2->middle=NULL;
            }
        }
        p2->val=value;
    }
    else if(i==strlen(s)){last->val=value;}
}
void search_propel()
{
    char s[100];
    scanf("%s",s);
    printf("%d",search(s));//如果输出0，则表示NOT FOUND
}
int search(char* s)
{
    tst* p=root,*last;
    int i=0;
    while(p!=NULL&&i<strlen(s)){
        last=p;
        if(s[i]==p->c){i++;p=p->middle;}
        else if(s[i]<p->c){p=p->left;}
        else if(s[i]>p->c){p=p->right;}
    }
    if(i<strlen(s))return 0;
    else return last->val;
}