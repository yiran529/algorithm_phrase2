#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main()
{
    char pat[100],txt[1000];
    printf("Input the pattern string:");scanf("%s",pat);
    printf("Input the text string:");scanf("%s",txt);
    int i,rightmost[200],skip,j=-1;
    memset(rightmost,-1,200*sizeof(int));
    //rightmost数组记录pat中每个字符最后一次出现的位置若相应字符没有出现则值为-1
    for(i=0;i<strlen(pat);i++)rightmost[pat[i]]=i;
    for(i=0;i<strlen(txt)-strlen(pat)+1;i+=skip){
        for(j=i+strlen(pat)-1;j>=i;j--){if(pat[j-i]!=txt[j])break;}
        if(j+1==i){printf("%d",i);break;}
        else{skip=fmax(1,j-i-rightmost[txt[j]]);}//1是为了避免右边那个值为负数
    }
    if(i>=strlen(txt)-strlen(pat)+1)printf("NOT FOUND!");
    return 0;
}