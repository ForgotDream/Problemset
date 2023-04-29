#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
typedef long long i64;
struct EDGE
{
	int to,w,Next,from;
}edge[100005<<1];
int head[100005],total;
void add_edge(int x,int y,int w)
{
	edge[++total]={y,w,head[x],x};
	head[x]=total;
}
int dfn[100005],low[100005],Cnt,stk[100005],top,col[100005],color,Size[100005];
bool instk[100005];
void tarjan(int pos)
{
	dfn[pos]=low[pos]=++Cnt;
	stk[++top]=pos;
	instk[pos]=true;
	for(int e=head[pos],Next;e;e=edge[e].Next)
	{
		Next=edge[e].to;
		if(!dfn[Next])
		{
			tarjan(Next);
			low[pos]=min(low[pos],low[Next]);
		}
		else if(instk[Next])
			low[pos]=min(low[pos],dfn[Next]);
	}
	if(dfn[pos]==low[pos])
	{
		int temp;
		color++;
		do
		{
			temp=stk[top--];
			instk[temp]=false;
			col[temp]=color;
			Size[color]++;
		}while(temp!=pos);
	}
	return;
}
int n,m,in[100005];
long long dp[100005];
void topo()
{
	queue<int>q;
	for(int i=1;i<=color;i++)
		if(!in[i]) {q.push(i);dp[i]=1;}
	int pos;
	while(!q.empty())
	{
		pos=q.front();q.pop();
		for(int e=head[pos],y;e;e=edge[e].Next)
		{
			y=edge[e].to;
            std::cerr << edge[e].w << "\n";
			if(!(--in[y])) q.push(y);
			dp[y]=max(dp[y],dp[pos]+edge[e].w);
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,order,x,y;i<=m;i++)
	{
		cin>>order>>x>>y;
		switch (order)
		{
			case 1:
				add_edge(x,y,0);
				add_edge(y,x,0);
				break;
			case 2:
				add_edge(x,y,1);
				break;
			case 3:
				add_edge(y,x,0);
				break;
			case 4:
				add_edge(y,x,1);
				break;
			case 5:
				add_edge(x,y,0);
				break;
			default : 
				break;
		}
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	memset(head, 0, sizeof(head));
	int PreTotal=total;
	total=0;
	for(int i=1,x,y;i<=PreTotal;i++)
	{
		x=col[edge[i].from],y=col[edge[i].to];
		if(x!=y)
		{
			add_edge(x,y,edge[i].w);
			in[y]++;
		}
		else if(edge[i].w)
		{
			cout<<-1;
			return 0;
		}
	}  
	topo();
	long long ans=0;
	for(int i=1;i<=color;i++) {
		ans+=dp[i]*Size[i];
    }
	cout<<ans;
	return 0;
}