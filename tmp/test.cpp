//#define ice
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
#define rint register int
using namespace std;
inline int read(){
	int res=0;char c=getchar(),f=1;
	while(c<48||c>57){if(c=='-')f=0;c=getchar();}
	while(c>=48&&c<=57)res=(res<<3)+(res<<1)+(c&15),c=getchar();
	return f?res:-res;
}

const int N=1e5+5,M=170,S=320;

int n,m,a[N],sz,vsz,mxv;
int k,L[M],R[M],bel[N];
int l,r,x,y,op,lb,rb;

int fa[N],rt[M][N];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int cnt[M][N],sumc[M][N],sums[M][S];

void build(int p){
	for(rint i=L[p];i<=R[p];++i){
		if(!rt[p][a[i]])rt[p][a[i]]=i;
		else fa[i]=rt[p][a[i]];
		++cnt[p][a[i]];
	}
}

int sta[N];
/* void update(int p,int l,int r,int x,int y){
	rint tmp=0,l0=L[p],r0=R[p],top=0;
	rt[p][x]=rt[p][y]=0;
	for(rint i=l0;i<=r0;++i){
		a[i]=a[find(i)];
		if(a[i]==x||a[i]==y)sta[++top]=i;
	}
	for(rint i=l;i<=r;++i)if(a[i]==x)a[i]=y,++tmp;
	for(rint i=1;i<=top;++i)fa[sta[i]]=sta[i];
	for(rint i=1,t,w;i<=top;++i){
		t=sta[i],w=a[t];
		if(!rt[p][w])rt[p][w]=t;
		else fa[t]=rt[p][w];
	}
	cnt[p][x]-=tmp,cnt[p][y]+=tmp;
	for(rint i=p;i<=k;++i){
		sumc[i][x]-=tmp,sumc[i][y]+=tmp;
		if(bel[x]!=bel[y])
			sums[i][bel[x]]-=tmp,sums[i][bel[y]]+=tmp;
	}
} */
void update(int p,int l,int r,int x,int y){
	rint tmp=0,l0=L[p],r0=R[p],top=0;
	rt[p][x]=rt[p][y]=0;
	for(rint i=l0;i<=r0;++i)a[i]=a[find(i)];
	for(rint i=l;i<=r;++i)if(a[i]==x)a[i]=y,++tmp;
  for(rint i=l0;i<=r0;++i)fa[i]=i;
  for(rint i=l0;i<=r0;++i){
    if(!rt[p][a[i]])rt[p][a[i]]=i;
    else fa[i]=rt[p][a[i]];
  }
	cnt[p][x]-=tmp,cnt[p][y]+=tmp;
	for(rint i=p;i<=k;++i){
		sumc[i][x]-=tmp,sumc[i][y]+=tmp;
		if(bel[x]!=bel[y])
			sums[i][bel[x]]-=tmp,sums[i][bel[y]]+=tmp;
	}
}

int c[N],s[S];
int main(){
#ifdef ice
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	n=read(),m=read();
	sz=600,vsz=317,mxv=1e5;
	k=(n-1)/sz+1;
	for(rint i=1;i<=n;++i)a[i]=read(),fa[i]=i;
	for(rint i=1;i<=mxv;++i)bel[i]=(i-1)/vsz+1;
	for(rint i=1;i<=k;++i){
		L[i]=(i-1)*sz+1,R[i]=min(i*sz,n);
		build(i);
		for(rint j=1;j<=vsz;++j)
			sums[i][j]=sums[i-1][j];
		for(rint j=1;j<=mxv;++j)
			sumc[i][j]=sumc[i-1][j]+cnt[i][j];
		for(rint j=L[i];j<=R[i];++j)
			++sums[i][bel[a[j]]];
	}
	while(m--){
		op=read();
		if(op==1){
			l=read(),r=read(),x=read(),y=read();
			if(x==y)continue;
			lb=(l-1)/sz+1,rb=(r-1)/sz+1;
			if(lb==rb)update(lb,l,r,x,y);
			else{
				update(lb,l,R[lb],x,y);
				update(rb,L[rb],r,x,y);
				rint tmp,tmps=0;
				for(rint i=lb+1;i<rb;++i){
					if(rt[i][x]){
						if(!rt[i][y])rt[i][y]=rt[i][x],a[rt[i][x]]=y;
						else fa[rt[i][x]]=rt[i][y];
						rt[i][x]=0,tmp=cnt[i][x],tmps+=tmp,
						cnt[i][y]+=tmp,cnt[i][x]=0;
					}
					sumc[i][x]-=tmps,sumc[i][y]+=tmps;
					if(bel[x]!=bel[y])
						sums[i][bel[x]]-=tmps,sums[i][bel[y]]+=tmps;
				}
				for(rint i=rb;i<=k;++i){
					sumc[i][x]-=tmps,sumc[i][y]+=tmps;
					if(bel[x]!=bel[y])
						sums[i][bel[x]]-=tmps,sums[i][bel[y]]+=tmps;
				}
			}
		}else{
			l=read(),r=read(),x=read();
			lb=(l-1)/sz+1,rb=(r-1)/sz+1;
			if(lb==rb){
				for(rint i=l;i<=r;++i)
					a[i]=a[find(i)],++c[a[i]],++s[bel[a[i]]];
				rint vl,vr,tmp=0;
				for(rint i=1;i<=vsz;++i){
					tmp+=s[i];
					if(tmp>=x){tmp-=s[i],vl=(i-1)*vsz+1,vr=i*vsz;break;}
				}
				for(rint i=vl;i<=vr;++i){
					tmp+=c[i];
					if(tmp>=x){printf("%d\n",i);break;}
				}
				for(rint i=l;i<=r;++i)
					--c[a[i]],--s[bel[a[i]]];
			}
			else{
				for(rint i=l;i<=R[lb];++i){
					a[i]=a[find(i)];
					++c[a[i]],++s[bel[a[i]]];
				}
				for(rint i=L[rb];i<=r;++i){
					a[i]=a[find(i)];
					++c[a[i]],++s[bel[a[i]]];
				}
				rint vl,vr,tmp=0;
				for(rint i=1;i<=vsz;++i){
					tmp+=s[i]+sums[rb-1][i]-sums[lb][i];
					if(tmp>=x){tmp-=s[i]+sums[rb-1][i]-sums[lb][i],vl=(i-1)*vsz+1,vr=i*vsz;break;}
				}
				for(rint i=vl;i<=vr;++i){
					tmp+=c[i]+sumc[rb-1][i]-sumc[lb][i];
					if(tmp>=x){printf("%d\n",i);break;}
				}
				for(rint i=l;i<=R[lb];++i)
					--c[a[i]],--s[bel[a[i]]];
				for(rint i=L[rb];i<=r;++i)
					--c[a[i]],--s[bel[a[i]]];
			}
		}
	}return 0;
}
