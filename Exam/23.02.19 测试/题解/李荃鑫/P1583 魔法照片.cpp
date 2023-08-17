#include<bits/stdc++.h>

using namespace std;

#define int long long

int read(){
    int a=0;int f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {a=(a<<1)+(a<<3)+ch-'0';ch=getchar();}
    return a*f;
}
int n,k,e[20];
struct node{
    int w,d,num,c;
}p[500500];
bool cmp2(node l,node r){
    if(l.w==r.w)return l.num<r.num;
    return l.w>r.w;
}
signed main(){
    freopen("photo.in","r",stdin);
    freopen("photo.out","w",stdout);
    n=read();k=read();
    for(int i=1;i<=10;i++)e[i]=read();
    for(int i=1;i<=n;i++){
        p[i].w=read();
        p[i].num=i; 
    }
    sort(p+1,p+1+n,cmp2);
    for(int i=1;i<=n;i++){
        p[i].d=i;
        p[i].c=((p[i].d-1)%10)+1;   
        p[i].w+=e[p[i].c];
    }
    sort(p+1,p+1+n,cmp2);
    for(int i=1;i<=k;i++){
        printf("%lld ",p[i].num);
    }
    return 0;
}