#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define rep(i,x,y) for(int (i)=(x);(i)<=(y);(i)++)
#define frep(i,x,y) for(int (i)=(x);(i)>=(y);(i)--)
using namespace std;
const int N=1e5+10;

struct
Edge
{
	int to;
	int Next;
}e[N<<1|1];
int head[N+1],cnt;
int dis[2][N+1],centre,maxdis;
int n;

void
dfs(int u,int fa,int *dis)
{
	//dis[u]=0;
	for(int i=head[u];i;i=e[i].Next)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dis[v]=dis[u]+1;
		dfs(v,u,dis);
	}
}

void
add(int u,int v)
{
	e[++cnt]=(Edge){v,head[u]};
	head[u]=cnt;
}

int
main()
{
	freopen("sb.in","r",stdin);
	freopen("sb.out","w",stdout);
	scanf("%d",&n);
	rep(i,1,n-1)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dfs(1,0,dis[0]);
	rep(i,1,n)
	{
		if(dis[0][i]>maxdis)
			centre=i,maxdis=dis[0][i];
	}
	dis[0][centre]=0;
	dfs(centre,0,dis[0]);
	centre=0;maxdis=0;
	rep(i,1,n)	if(dis[0][i]>maxdis)
		centre=i,maxdis=dis[0][i];
	//dis[centre]=0;
	dfs(centre,0,dis[1]);
	rep(i,1,n)	
		printf("%d\n",max(dis[0][i],dis[1][i]));
	return 0;
}
