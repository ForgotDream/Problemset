#include <cstdio>
#include <queue>
#include <utility>
using namespace std;

typedef pair <int,int>  PII;
const int N=250010,M=500010;
struct edge{int s,t,d,n;}e[2*M];
int n,m,A,B,h[N],r[N],g[N],dis[N];
priority_queue <PII,vector <PII>,greater <PII> > Q;

void work()
{
	scanf("%d %d %d %d",&n,&m,&A,&B);
	for (int i=1; i<=n; i++)
		scanf("%d %d",&r[i],&g[i]),dis[i]=1<<30;
	for (int i=1,u,v,w,tot=1; i<=m; i++)
	{
		scanf("%d %d %d",&u,&v,&w);
		e[++tot]=(edge){u,v,w,h[u]},h[u]=tot;
		e[++tot]=(edge){v,u,w,h[v]},h[v]=tot;
	}
	dis[A]=0,Q.push(make_pair(0,A));
	while (!Q.empty())
	{
		int x=Q.top().second,d=Q.top().first;
		Q.pop();
		if (x==B)  break;
		if (dis[x]<d)  continue;
		if (d%(r[x]+g[x])<r[x])  d+=r[x]-d%(r[x]+g[x]);
		for (int i=h[x],y; y=e[i].t,i; i=e[i].n)
			if (d+e[i].d<=dis[y])
				dis[y]=d+e[i].d,Q.push(make_pair(dis[y],y));
	}
	printf("%d",dis[B]);
}

int main()
{
	freopen("traffic.in","r",stdin);
	freopen("traffic.out","w",stdout);
	work();
	return 0;
}
