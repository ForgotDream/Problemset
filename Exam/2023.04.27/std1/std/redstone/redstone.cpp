#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#define For(x,y,z) for(int x=y;x<=z;x++)
using namespace std;
const int N=1e5+10;
vector<int>e[N],e2[N],e3[N];
queue<int>q;
int t[N],in[N],out[N],dis[N],n,ans;
bool mark[N],vis[N];
void tp_sort()
{
	For(i,1,n) 
	{
		if(!in[i]) q.push(i),e2[i].push_back(0),e2[0].push_back(i);
		if(!out[i]) e[i].push_back(n+1),e3[n+1].push_back(i);
	}
	while(q.size())
	{
		int cur=q.front();
		q.pop();
		for(int i=0;i<e[cur].size();i++)
		{
			int nt=e[cur][i];
			in[nt]--;
			dis[nt]=max(dis[nt],dis[cur]+t[cur]);
			if(in[nt]==0) q.push(nt);
		}
	}
}
void build(int cur)
{
	for(int i=0;i<e3[cur].size();i++)
	{
		int nt=e3[cur][i];
		if(dis[nt]+t[nt]==dis[cur]) e2[nt].push_back(cur),e2[cur].push_back(nt),build(nt);
	}
}
int dfn[N],low[N],tot,now;
void tarjan(int cur)
{
	dfn[cur]=low[cur]=++tot;
	for(int i=0;i<e2[cur].size();i++)
	{
		int nt=e2[cur][i];
		if(!dfn[nt])
		{
			tarjan(nt);
			if(cur!=0&&cur!=now&&low[nt]>=dfn[cur]&&!mark[cur]) 
			{
				mark[cur]=1;
				ans++;
			}
			low[cur]=min(low[cur],low[nt]);
		}
		else low[cur]=min(low[cur],dfn[nt]);
	}
}
int main()
{
	freopen("redstone.in","r",stdin);
	freopen("redstone.out","w",stdout);
	scanf("%d",&n);
	now=n+1;
	For(i,1,n)
	{
		int c;
		scanf("%d%d",&t[i],&c);
		in[i]+=c;
		while(c--)
		{
			int v;
			scanf("%d",&v);
			e[v].push_back(i);
			e3[i].push_back(v);
			out[v]++;
		}
	}
	tp_sort();
	build(n+1);
	printf("%d\n",dis[n+1]);
	tarjan(n+1);
	printf("%d\n",ans);
	For(i,1,n)
		if(mark[i]) printf("%d ",i);
	return 0;
}
