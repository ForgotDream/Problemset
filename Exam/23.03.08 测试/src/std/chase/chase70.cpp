#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+5;
struct abc{
	long long t,v,x;
	bool operator < (const abc &p) const {
		if(x^p.x)	return x<p.x;
		return v<p.v;
	}
} a[N];
int n,k;
double s;
inline int r(){
	int p=0;char c=getchar();
	while(c>57||c<48)	c=getchar();
	while(c<58&&c>47)	p=(p<<1)+(p<<3)+(c^48),c=getchar();
	return p;
}
int main(){
	freopen("chase.in","r",stdin);
	freopen("chase.out","w",stdout);
	n=r();
	for(int i=1;i<=n;i++)	a[i].t=r(),a[i].v=r(),k=k>a[i].t?k:a[i].t;
	for(int i=1;i<=n;i++)	a[i].x=(k-a[i].t)*a[i].v;
	sort(a+1,a+n+1);
	if(a[1].v<=a[n].v)	printf("%.2lf",1.0*a[n].x);
	else if(n==2)	puts("0.00");
	return 0;
}
