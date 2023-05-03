#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int tree[205];
inline int Find(int x)
{
	while (x!=tree[x])
		x=tree[x]=tree[tree[x]];
	return x;
}
struct EDGE
{
	int to,Next,w;
}edge[20005];
int head[205],total;
int in[205];
inline void add_edge(int u,int v,int w)
{
	in[v]++;
	edge[++total]=EDGE{v,head[u],w};
	head[u]=total;
}
int n,m,q;
int dis[205];
bool inq[205];
inline void spfa(int s)
{
	for (int i=1;i<=m;i++)
		dis[i]=-0x3f3f3f3f;
	queue<int>q;
	q.push(s);
	inq[s]=true;
	dis[s]=0;
	int pos;
	while (!q.empty())
	{
		pos=q.front();
		q.pop();
		inq[pos]=false;
		for(int e=head[pos],Next;e;e=edge[e].Next)
		{
			Next=edge[e].to;
			if (dis[Next]<dis[pos]+edge[e].w)
			{
				dis[Next]=dis[pos]+edge[e].w;
				if (!inq[Next])
				{
					inq[Next]=true;
					//tree[Next]=s;
					q.push(Next);
				}
			}
		}
	}
}
int main()
{
	freopen("differ.in","r",stdin);
	freopen("differ.out","w",stdout);
	//memset(dis,0x3f,sizeof(dis));
	scanf("%d %d",&m,&n);
	for (int i=1;i<=m;i++)
		tree[i]=i;
	for (int i=1,type,x,y,w;i<=n;i++)
	{
		scanf("%d %d %d %d",&type,&x,&y,&w);
		if (type==0)
		{
			//x-y<=w
			add_edge(x,y,-w);
		}
		else if (type==1)
		{
			//x-y>=w
			add_edge(y,x,w);
		}
		else if (type==2)
		{
			//x-y==w
			add_edge(y,x,w);
			add_edge(x,y,-w);
		}
	}
	/*for (int i=1;i<=m;i++)
		if (in[i]==0)
			spfa(i);
	for (int i=1;i<=m;i++)
		printf("%d ",dis[i]);
	putchar('\n');
	for (int i=1;i<=m;i++)
		printf("%d ",tree[i]);*/
	scanf("%d",&q);
	int x,y;
	while (q--)
	{
		scanf("%d %d",&x,&y);
		spfa(x);
		if (dis[y]==-0x3f3f3f3f)
		{
			printf("Infinity\n");
			continue;
		}
		printf("%d\n",dis[x]-dis[y]);
		//query max(x-y);
	}
	return 0;
}
/*
4 3
0 1 2 10
1 2 3 -5
2 1 3 -2
2
1 3
1 4
*/

