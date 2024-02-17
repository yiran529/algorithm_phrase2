#include<stdio.h>
#include<stdlib.h>
typedef struct NODE{
    int value;//存放ASCII码值或数值本身
    struct NODE *pre,*next;
}node;
void push(node** headp,node** tailp,int value);
void _pop(node** headp,node** tailp,node* p);
//这个操作事实上已经破坏了栈的先进后出的性质,它更像是链表中删除节点的操作
void Rpara(node** headp1,node** tailp1,node** headp2,node** tailp2);
//处理遇到右括号的情况
int main()
{
    char c,save="";
    int num=0,negative=0;
    node* Valhead=NULL,*Valtail=NULL,*Oprhead=NULL,*Oprtail=NULL;
    printf("Input an expression consisting of numbers,"
                " parenthesis and operations (MAKE SURE IT IS LEGAL!):");
    while((c=getchar())!='\n'){
        if(c!=' '){
            if(c>='0'&&c<='9'){
                num=num*10+c-'0';
            }
            else if(save>='0'&&save<='9'){
                if(negative==1)num=-num;
                push(&Valhead,&Valtail,num);
                negative=0;
            }
            if(c=='+'||c=='*'||c=='/')push(&Oprhead,&Oprtail,c);
            else if(c=='-'){
                if(save!='('&&save!="")push(&Oprhead,&Oprtail,c);
                else negative=1;
            }
            else if(c=='(')push(&Valhead,&Valtail,INT_MAX);
/*以INT_MAX代指右括号；另外这里与Dijkstra的算法不同的是，我们让左括号进入数值栈，
  从而便于处理诸如(1+2*3)的情况，这是原始算法不考虑的*/      
            else if(c==')'){
                Rpara(&Valhead,&Valtail,&Oprhead,&Oprtail);
            }
            save=c;
        }
    }
    //最后需要再检查一次
    return 0;
}
void push(node** headp,node** tailp,int value){
    node *p=(node*)malloc(sizeof(node));
    p->value=value,p->pre=*tailp,p->next=NULL;
    if(*headp==NULL)*headp=p;
    *tailp=p;
}
void pop(node** headp,node** tailp,node* p)
{
    if(p== *headp)*headp=NULL;
    else if(p==*tailp)*tailp=p->pre;//前面那个判断已经保证了p->pre不是空
    else{//前面两个判断已经保证接下来的操作不会出现段错误
        p->pre->next=p->next;
        p->next->pre=p->pre;
    }
}
void Rpara(node** headp1,node** tailp1,node** headp2,node** tailp2){
    node* p1=(*tailp1)->pre,*p2=*tailp2;int cnt=0;
    while(p1->value!=INT_MAX){
        p1=p1->pre;cnt++;
        if(p2->pre->value!=INT_MAX)p2=p2->pre;
        //不用担心p2->pre是NULL，因为先行判断了p2->value
    }
    p1=p1->next;
    while(p1!=*tailp1){//检查乘除的情况
        if(p2->value=='*')p1->value=p1->value*p1->next->value;
        else if(p2->value=='/')p1->value=p1->value/p1->next->value;
        if(p2->value=='*'||p2->value=='/'){
            pop(headp1,tailp1,p1->next);
            pop(headp2,tailp2,p2);
            // if(p1->next==*tailp1){
            //     free(*tailp1);free(*tailp2);
            //     tailp1=&p1;
            //     break;
            // }
            // node* save=p1->next;
            // p1->next=p1->next->next;
            // p1->next->pre=p1;
            // if(p2==*headp2)headp2=&(p2->next);//这里应该怎么写
            // p2->pre->next=p2->next;
            // p2->next->pre=p2->pre;
            // free(save);free(p2);
        }
        p1=p1->next;p2=p2->next;
    }
    //这会不会忽略这种情况? ...(-10)...
}
