# include <cstdio>
# include <cstring>
# include <algorithm>
# include <queue>
using namespace std;
typedef long long LL;
const LL N=1e3+5;
const LL M=2e6+5;
LL h,n;
LL dis[N];
struct point{LL dis;LL num;bool operator < (const point &A) const {return A.dis<dis;}};
priority_queue <point> q;

LL e[M],nt[M],hd[M],w[M],cnt;void bb(LL a,LL b,LL c){e[++cnt]=b;nt[cnt]=hd[a];hd[a]=cnt;w[cnt]=c;return ;}

LL x[N],y[N];

void spfa()
{
	memset(dis,63,sizeof(dis));
	dis[0]=0;
	q.push((point){0,0});
	while(!q.empty())
	{
		point tem=q.top();q.pop();
		LL a=tem.num;
		if(dis[a]<tem.dis) continue;
		for(LL i=hd[a];i;i=nt[i])
		{
			LL v=e[i];
			if(dis[v]>dis[a]+w[i])
			{
				dis[v]=dis[a]+w[i];
				q.push((point){dis[v],v});
			}
		}
	}
	return ;
}

signed main()
{
	freopen("wall.in","r",stdin);
	freopen("wall.out","w",stdout);
	scanf("%lld %lld",&h,&n);
	for(LL i=1;i<=n;i++)
	scanf("%lld %lld",&x[i],&y[i]);
	for(LL i=1;i<=n;i++)
	if(abs(y[i])<=1000) bb(0,i,1),bb(i,0,1);
	
	for(LL i=1;i<=n;i++)
	if(abs(y[i]-h)<=1000) bb(n+1,i,0),bb(i,n+1,0);
	
	for(LL i=1;i<=n;i++)
	for(LL j=i+1;j<=n;j++)
	if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<=1000000ll) bb(i,j,1),bb(j,i,1);
	
	spfa();
	
	printf("%lld",dis[n+1]);
	return 0;
}
