#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<string>
#include<cmath>
#define rep(i,x,y) for(int (i)=(x);(i)<=(y);(i)++)
#define frep(i,x,y) for(int (i)=(x);(i)>=(y);(i)--)
using namespace std;
const int N=1e3+10,M=5e5+10;
const long double Inf=1e30,Exp=1e-12;

int head[N+1],cnt;
long double g[N+1][N+1];
int n,m,k;
long double dis[N+1];
long double ans=Inf;
vector<int>a;

const char *s,*p1=s,*p2=s;
string buf;
#define getchar() (p1==p2?EOF:*p1++)
template<class _T>void
read(_T &x)
{
	x=0;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
		if(ch==EOF) return ;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch&15);
}

bool
chkmin(long double &a,long double b)
{
	if(b<a&&fabs(a-b)>Exp) {a=b;return 1;};
	return 0;
}

void
work()
{
	a.clear();
	long double sum=0.0;
	getline(cin,buf);
	if(buf=="I cannot solve this problem!")
		return ;
	s=buf.c_str();
	p1=s;p2=s+strlen(s);
	int now;bool flag=1;
	for(read(now);now;read(now))  
	{
		if(now>n) return ;
		a.push_back(now);
	}
	if(a.empty()) return ;
	int len=a.size();
	rep(i,0,len-1)
	{
		int u=a[i];
		if(i!=len-1)
		{
			int v=a[i+1];
			if(fabs(g[u][v]-Inf)<=Exp) 
			{
				flag=0;break;
			}
			sum+=g[u][v];
		}
	}
	int temp=a[len-1];
	if(flag&&temp==n) chkmin(ans,sum);
}

void
add(int u,int v,long double w)
{
	chkmin(g[u][v],w);
}

int
main()
{
	freopen("compare.in","r",stdin);
	freopen("compare.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,n) rep(j,1,n)
		if(i!=j) g[i][j]=Inf;
	rep(i,1,m)
	{
		int u,v;
		long double w;
		scanf("%d%d%Lf",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	//dij();
	getline(cin,buf);
	rep(i,1,k) 
		work();
	if(fabs(ans-Inf)<=Exp) puts("Wrong");
	else printf("%.4Lf",ans);
	return 0;
}
