#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<unordered_map>
#include<set>
#include<bitset>
#include<queue>
using namespace std;
struct EDGE
{
	int to,w,Next;
}edge[200005];
int head[5005],total;
inline void add_edge(int u,int v,int w)
{
	edge[++total]=EDGE{v,w,head[u]};head[u]=total;
}
int dis[2][5005];
//0 最短路 1 次短路 
int pre[5005];
bool inq[5005];
inline void spfa(int s)
{
	memset(dis,0x3f,sizeof(dis));
	dis[0][s]=0;
	queue<int>q;
	q.push(s);
	inq[s]=true;
	int pos;
	while (!q.empty())
	{
		pos=q.front();q.pop();
		inq[pos]=false;
		for(int e=head[pos],Next;e;e=edge[e].Next)
		{
			Next=edge[e].to;
			if (dis[0][pos]+edge[e].w<dis[0][Next])
			{
				dis[1][Next]=dis[0][Next];
				dis[0][Next]=dis[0][pos]+edge[e].w;
				if (!inq[Next])
					q.push(Next),inq[Next]=true;
			}
			else if (dis[0][pos]+edge[e].w<dis[1][Next]&&
					dis[0][pos]+edge[e].w!=dis[0][Next])
			{
				dis[1][Next]=dis[0][pos]+edge[e].w;
				if (!inq[Next])
					q.push(Next),inq[Next]=true;
			}
		}
	}
}
int n,m;
int main()
{
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d %d %d",&x,&y,&z);
		add_edge(x,y,z);add_edge(y,x,z);
	}
	spfa(1);
	printf("%d",dis[1][n]);
	return 0;
}
