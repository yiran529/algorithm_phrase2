#include<iostream>
#include<set>
#include<cmath>
#include<queue>
#include<algorithm>
struct matrix{
    int n[4][4];
    bool operator<(matrix x) const {
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
            if (n[i][j] != x.n[i][j]) return n[i][j] < x.n[i][j];
        return false;
    }
}ini,tar;

int h(struct matrix x){
    int cnt=0;
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            if(x.n[i][j]!=tar.n[i][j])cnt++;
    return cnt;
}
struct node{
    matrix a;
    int g;
    bool operator<(node x) const{return g+h(a)>x.g+h(x.a);}////为什么是小于号
};
using namespace std;
int main()
{
    int ch[5][3];
    ch[1][1]=1;ch[1][2]=0;
    ch[2][1]=0;ch[2][2]=1;
    ch[3][1]=-1;ch[3][2]=0;
    ch[4][1]=0;ch[4][2]=-1;
    tar.n[1][1]=1;
    tar.n[1][2]=2;
    tar.n[1][3]=3;
    tar.n[2][1]=8;
    tar.n[2][2]=0;
    tar.n[2][3]=4;
    tar.n[3][1]=7;
    tar.n[3][2]=6;
    tar.n[3][3]=5;
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++){
            char c;cin>>c;
            ini.n[i][j]=c-'0';
        }
    priority_queue<node> pq;
    set<matrix> st;//st表示closed集
    struct node x={ini,0};
    pq.push(x);
    while(!pq.empty()){
        struct node cur=pq.top();
        pq.pop(); 
        if(st.count(cur.a))continue;
        st.insert(cur.a);//按照网络上的资料，这句话更应该放在这里而非后面的二重循环里？
        if(h(cur.a)==0){cout<<cur.g;return 0;}
        int zerox,zeroy;
        for(int i=1;i<=3;i++)
            for(int j=1;j<=3;j++){
                if(cur.a.n[i][j]==0){zerox=i;zeroy=j;}
            }
        for(int i=1;i<=4;i++){
            int newx=zerox+ch[i][1],newy=zeroy+ch[i][2];
            if(1<=newx&&newx<=3&&1<=newy&&newy<=3){
                swap(cur.a.n[zerox][zeroy],cur.a.n[newx][newy]);
                if(!st.count(cur.a)) pq.push((node){cur.a,cur.g+1});
                swap(cur.a.n[zerox][zeroy],cur.a.n[newx][newy]);//Don't forget this!
            }        
        }
    }
    return 0;
}