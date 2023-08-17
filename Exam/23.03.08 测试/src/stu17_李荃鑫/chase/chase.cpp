#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,maxv,vi,ti;
double maxt;
struct node{
	double t,v;
}a[100050];
inline bool cmp(node l,node r){
	if(l.v==r.v)return l.t>r.t;
	return l.v<r.v;
}
inline double clac(int i,int j){
	return (double)(a[i].v*a[i].t-a[j].v*a[j].t)/(a[i].v-a[j].v);
}
signed main(){
	freopen("chase.in","r",stdin);
	freopen("chase.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i].t=read();
		a[i].v=read();
		maxt=max(a[i].t,maxt);
	}
	if(n==2){
		printf("0.00");
		return 0;
	}
	sort(a+1,a+1+n,cmp);
	double ans=0,maxl,minl=1e14;
	for(int i=1;i<=n;i++){
		maxl=max(maxl,a[i].v*(maxt-a[i].t));
		minl=min(minl,a[i].v*(maxt-a[i].t));
	}
	ans=maxl-minl;
	for(int l=1;l<n;l++){
		double jx=clac(n,l);
		if(jx<maxt)continue;
		maxl=0;minl=1e14;
		for(int i=1;i<=n;i++){
			maxl=max(maxl,a[i].v*jx-a[i].v*a[i].t);
			minl=min(minl,a[i].v*jx-a[i].v*a[i].t);
		}
		if(maxl==a[n].v*jx-a[n].v*a[n].t)break;
		if(minl==1e14)continue;
		ans=min(ans,maxl-minl);
	}
	printf("%.2lf",ans);
	return 0;
}
