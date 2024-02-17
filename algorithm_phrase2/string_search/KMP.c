#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int (*construct_dfa(char* pat))[100];
void search(char* txt,int (*dfa)[100],int len);
int main()
{
    char pat[100],txt[1000];
    printf("Input the pattern string:");scanf("%s",pat);
    printf("Input the text string:");scanf("%s",txt);
    int(*dfa)[100]=construct_dfa(pat);
    search(txt,dfa,strlen(pat));
}
int (*construct_dfa(char* pat))[100]
{
    int i,j=0,x=0;
    int (*dfa)[100]=(int(*)[100])malloc(20000*sizeof(int));
    for(i=1;i<=strlen(pat);i++)dfa[pat[i]][0]=0;
    for(i=0;i<strlen(pat);i++){
        dfa[pat[i]][i]=i+1;
        for(j=0;j<strlen(pat);j++){
            if(pat[i]!=pat[j])dfa[pat[j]][i]=dfa[pat[j]][x];//注意这里有个判断条件
        }
        if(i!=0)x=dfa[pat[i]][x];//务必注意i不能等于0
    }
    return dfa;
}
void search(char*txt,int (*dfa)[100],int len)
{
    int i,j;
    for(i=0,j=0;j<len&&i<strlen(txt);i++)
        j=dfa[txt[i]][j];
    if(j==len)printf("%d",i-len);//第一次出现pattern字符串的位置
    else printf("NOT FOUND!");
    free(dfa);
}