#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int N=100010;
int n,t[N],d[N],ans[N],ans2[N];
vector <int> E[N],EE[N],res;
queue <int> Q;

struct graph{
	vector <int> E[N],cp;
	int dfn[N],low[N],tot;

	void addedge(int x,int y)
		{
			E[x].push_back(y);
			E[y].push_back(x);
		}

	void tarjan(int x,int f)
		{
			int s=0,t=0;
			dfn[x]=low[x]=++tot;
			for (int i=0; i<E[x].size(); i++)
			{
				int y=E[x][i];
				if (y!=f)
				{
					s++;
					if (!dfn[y])
					{
						tarjan(y,x),low[x]=min(low[x],low[y]);
						if (low[y]>=dfn[x])  t=1;
					}else  low[x]=min(low[x],dfn[y]);
				}
			}
			if (((f!=-1)&&(t==1))||((f==-1)&&(s>1)))  res.push_back(x);
		}

	vector <int> solve()
		{
			tarjan(0,-1);
			return res;
		}
}G;

void addedge(int x,int y)
{
	E[x].push_back(y);
	EE[y].push_back(x);
}

void solve(vector <int> *E,int *ans)
{
	for (int i=0; i<=n+1; i++)
		for (int j=0; j<E[i].size(); j++)
			{
				int y=E[i][j];
				d[y]++;
		    }
	for (int i=0; i<=n+1; i++)
		if (!d[i])  Q.push(i);
	while (!Q.empty())
	{
		int x=Q.front();
		Q.pop(),ans[x]+=t[x];
		for (int i=0; i<E[x].size(); i++)		
		{	int y=E[x][i];
			ans[y]=max(ans[y],ans[x]);
			if (!(--d[y]))  Q.push(y);
		}
	}
}

void work()
{
	scanf("%d",&n);
	for (int i=1,m,x; i<=n; i++)
	{
		scanf("%d %d",&t[i],&m);
		if (!m)  addedge(0,i);
		addedge(i,n+1);
		for (int j=1; j<=m; j++)
			scanf("%d",&x),addedge(x,i);;
	}
	solve(E,ans);
	solve(EE,ans2);

	ans2[0]=0;
	for (int i=0; i<=n+1; i++)
		for (int j=0; j<E[i].size(); j++)
		{
			int y=E[i][j];
			if (ans[i]+ans2[y]==ans[n+1])
				G.addedge(i,y);
		}	
	res=G.solve();
	
	sort(res.begin(),res.end());
	printf("%d\n%d\n",ans[n+1],res.size());
	for (int x=0; x<res.size(); x++)  printf("%d ",res[x]);
}

int main()
{
	freopen("redstone.in","r",stdin);
	freopen("redstone.out","w",stdout);
	work();
	return 0;
}
