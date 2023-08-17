#include<cstdio>
typedef long long ll;
const int N=5e3+5,M=1e8;
int a[N],b[N],c[N],d[N],A,B,C,D;
int p[M+5],q[M+5],n,k;
ll s,t;
inline int r(){
	int p=0;char c=getchar();
	while(c>57||c<48)	c=getchar();
	while(c<58&&c>47)	p=(p<<1)+(p<<3)+(c^48),c=getchar();
	return p;
}
void f(int x,int y[])	{for(int i=0;i<x;i++)	y[i]=r();}
int main(){
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
	n=r();A=r();B=r();C=r();D=r();
	f(A,a);f(B,b);f(C,c);f(D,d);
	for(int i=0;i<A;i++)
		for(int j=0;j<B;j++)
			if(a[i]+b[j]<=n)	p[a[i]+b[j]]++;
	for(int i=0;i<C;i++)
		for(int j=0;j<D;j++)
			if(c[i]+d[j]<=n)	q[c[i]+d[j]]++;
	for(int i=n;~i;i--)
		if(p[i]){
			for(;k<=n-i;k++)	t+=q[k];
			s+=t*p[i];
		}
	printf("%lld",s);
	return 0;
}
