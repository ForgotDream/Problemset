#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define maxn 1000005
#define ll long long 
using namespace std;

int n,m,d,i,j,k,ans;
int em,e[maxn*2],nx[maxn*2],ls[maxn*2];
ll f[maxn*2];

void read(int &x){
	x=0; char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
}

void insert(int x,int y){
	em++; e[em]=y; nx[em]=ls[x]; ls[x]=em;
}

int dep[maxn*2],g[maxn*2],dfn[maxn*2],mxd[maxn*2],lim[maxn*2],tot,fa[maxn*2];
void dfs1(int x,int p){
	dep[x]=dep[p]+1,g[x]=0,mxd[x]=dep[x],fa[x]=p;
	for(int i=ls[x];i;i=nx[i]){
		dfs1(e[i],x);
		if (mxd[e[i]]>mxd[x]) 
			mxd[x]=mxd[e[i]],g[x]=e[i];
	}
}

void getlim(int x,int p,int d0){
	int mxd1=d0,id1=p,mxd2=0,id2=0;
	for(int i=ls[x];i;i=nx[i]){
		int y=e[i];
		if (mxd[y]-dep[x]>mxd1) mxd2=mxd1,id2=id1,mxd1=mxd[y]-dep[x],id1=y; else
		if (mxd[y]-dep[x]>mxd2) mxd2=mxd[y]-dep[x],id2=y;
	}
	lim[x]=mxd2;
	for(int i=ls[x];i;i=nx[i])
		getlim(e[i],x,(id1==e[i])?mxd2+1:mxd1+1);
}

void dfs2(int x,int p){
	dfn[x]=++tot,f[dfn[x]]=(x<=n);
	if (g[x]) dfs2(g[x],x);
	for(int i=ls[x];i;i=nx[i]) if (e[i]!=g[x]){
		int y=e[i]; dfs2(y,x);
		for(int j=dep[y];j<=mxd[y];j++)
			f[dfn[x]+j-dep[x]]+=f[dfn[e[i]]+j-dep[e[i]]];
	}
}

int st,R[maxn*2];
ll f0[maxn*4],tag,tag0;
int count(int x,int d){return f[dfn[x]+d]+f0[st+d]+tag+tag0;}
void dfs3(int x,int p){
	ll Tag0=tag0; if (g[p]!=x) tag0=0;
	st--,f0[st]=-tag;
	if (p==0) {
		R[x]=lim[x];
		for(int i=0;i<lim[x];i++) if (count(x,i)>=m){
			R[x]=i;
			break;
		}
	} else {
		if (count(x,lim[x])<m) R[x]=lim[x]; else {
			if (R[p]>0&&count(x,R[p]-1)>=m) R[x]=R[p]-1; else 
			if (count(x,R[p])>=m) R[x]=R[p]; else 
				R[x]=R[p]+1;
		}
	}
		
	if (count(x,R[x])>=m&&d-R[x]>=0)
		ans=max(ans,count(x,min(mxd[x]-dep[x],d-R[x])));
	tag+=(x<=n);
	for(int i=ls[x];i;i=nx[i]) if (e[i]!=g[x]){
		int y=e[i];
		for(int j=1;j<mxd[y]-dep[y];j++)
			f0[st+j]+=f[dfn[x]+j]+tag0-f[dfn[y]+j-1]-(x<=n);
		dfs3(y,x);
		for(int j=1;j<mxd[y]-dep[y];j++)
			f0[st+j]-=f[dfn[x]+j]+tag0-f[dfn[y]+j-1]-(x<=n);
	}
	if (g[x]){
		tag0-=(x<=n);
		for(int i=ls[x];i;i=nx[i]) if (e[i]!=g[x]){
			int y=e[i],tmp=f[dfn[y]+mxd[y]-dep[y]];
			tag+=tmp,tag0-=tmp,f0[st]-=tmp;
			for(int j=0;j<=mxd[y]-dep[y];j++){
				f0[st+j+1]+=f[dfn[y]+j]-tmp;
				f[dfn[x]+j+1]-=f[dfn[y]+j]-tmp;
			}
		}
		dfs3(g[x],x);
		tag0+=(x<=n);
		for(int i=ls[x];i;i=nx[i]) if (e[i]!=g[x]){
			int y=e[i],tmp=f[dfn[y]+mxd[y]-dep[y]];
			tag-=tmp,tag0+=tmp,f0[st]+=tmp;
			for(int j=0;j<=mxd[y]-dep[y];j++)	{
				f0[st+j+1]-=f[dfn[y]+j]-tmp;
				f[dfn[x]+j+1]+=f[dfn[y]+j]-tmp;
			}
		}		
	}
	f0[st++]=0,tag-=(x<=n),tag0=Tag0;
}

int main(){
	read(n),read(m),read(d),d=d*2;
	for(i=2;i<=n;i++) read(k),insert(k,n+i-1),insert(n+i-1,i);
	dfs1(1,0),dfs2(1,0),getlim(1,0,0);
	for(int x=1;x<2*n;x++) if (g[fa[x]]!=x){
		for(i=dep[x]+1;i<=mxd[x];i++)
			f[dfn[x]+i-dep[x]]+=f[dfn[x]+i-dep[x]-1];
	}
	ans=0,st=2*n,dfs3(1,0);
	printf("%d\n",ans);
}
