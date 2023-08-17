#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;
const long double INF=(long double)1000000000*10;
long double L,R,mid,ans,hh[100005];
int r,rr,i,n,MAX,X,Y,cnt,vv[100005],vv2[100005];
struct node2 {int t; long double l;} s[200005],S[200005];
struct node {int t,v;} t[100005];
int cmp(node i,node j) {return i.v<j.v || i.v==j.v && i.t>j.t;}
struct Node {long double x;int y,z;} p[200005];
int CMP(Node i,Node j) {return i.x<j.x;}
long double work(int x,long double y) {return (long double)t[x].v*y-hh[x];}
int main()
{
    freopen("chase.in","r",stdin);
    freopen("chase.out","w",stdout);
    while (1)
    {
        scanf("%d",&n);
       // if (n==0) return 0;
        MAX=0;
        for (i=1; i<=n; i++)
        {
            scanf("%d%d",&t[i].t,&t[i].v);
            MAX=max(MAX,t[i].t);
        }
        sort(t+1,t+n+1,cmp); int MIN=t[n].t;
        for (i=n-1; i>=2; i--)
        {
            if (t[i].t>MIN) vv[i]=1; else
            MIN=t[i].t,vv[i]=0;
        }
        for (i=1; i<=n; i++) hh[i]=(long double)t[i].t*t[i].v;
        r=1; s[1].l=MAX; s[1].t=1; s[2].l=INF; vv[n]=0;
        for (i=2; i<=n; i++)
        if (!vv[i])
        {
            while (r && work(i,s[r].l)>=work(s[r].t,s[r].l)) r--;
            if (!r) {r=1; s[1].l=MAX; s[1].t=i; continue;}
            L=s[r].l; R=s[r+1].l; mid=(L+R)/2.0;
            for (int I=1; I<=80; I++)
            {
                if (work(i,mid)>=work(s[r].t,mid)) {R=mid; mid=(L+R)/2.0;} else {L=mid; mid=(L+R)/2.0;}
            }
            s[++r].l=mid; s[r].t=i; s[r+1].l=INF;
        }
        rr=1; S[1].l=MAX; S[2].l=INF; S[1].t=n;
        MIN=t[1].t;
        for (i=2; i<n; i++)
          if (t[i].t<MIN) vv2[i]=1; else
            MIN=t[i].t,vv2[i]=0;
        for (i=n-1; i>=1; i--)
        if (!vv2[i])
        {
            while (rr && work(i,S[rr].l)<=work(S[rr].t,S[rr].l)) rr--;
            if (!rr) {rr=1; S[1].l=MAX; S[1].t=i; continue;}
            L=S[rr].l; R=S[rr+1].l; mid=(L+R)/2.0;
            for (int I=1; I<=80; I++)
            {
                if (work(i,mid)<=work(S[rr].t,mid)) {R=mid; mid=(L+R)/2.0;} else {L=mid; mid=(L+R)/2.0;}
            }
            S[++rr].l=mid; S[rr].t=i; S[rr+1].l=INF;
        }
        cnt=0;
        for (i=1; i<=r; i++) {p[++cnt].x=s[i].l; p[cnt].y=1; p[cnt].z=s[i].t;}
        for (i=1; i<=rr; i++) {p[++cnt].x=S[i].l; p[cnt].y=0; p[cnt].z=S[i].t;}
        sort(p+1,p+cnt+1,CMP); X=Y=0; ans=INF;
        for (i=1; i<=cnt; i++)
        {
            if (p[i].y==1) X=p[i].z; else Y=p[i].z;
          //  printf("%.5f\n",(double)p[i].x);
            if (X && Y) ans=min(ans,work(X,p[i].x)-work(Y,p[i].x));
        }
        printf("%.2f\n",fabs((double)ans));
        return 0;
    }
}
