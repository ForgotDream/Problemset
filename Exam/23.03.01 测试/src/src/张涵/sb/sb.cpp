#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
struct EDGE
{
	int to,Next;
}edge[20005];
int head[10005],total;
inline void add_edge(int u,int v)
{
	edge[++total]=EDGE{v,head[u]};head[u]=total;
}
int n;
int deep[10005],size[10005],son[10005];
void dfs1(int s,int fa)
{
	deep[s]=deep[fa]+1;
	size[s]=1;son[s]=s;
	for (int e=head[s],Next;e;e=edge[e].Next)
	{
		Next=edge[e].to;
		if (Next==fa) continue;
		dfs1(Next,s);
		if (size[Next]>=size[son[s]]) son[s]=Next;
		size[s]+=size[Next];
	}
}
int top[10005],line_to_tree[10005],tree_to_line[10005],id;
void dfs2(int s,int fa,int tp)
{
	tree_to_line[s]=++id;
	line_to_tree[id]=s;
	top[s]=tp;
	if (son[s]&&s!=son[s]) dfs2(son[s],s,tp);
	for (int e=head[s],Next;e;e=edge[e].Next)
	{
		Next=edge[e].to;
		if (Next==fa||Next==son[s]) continue;
		dfs2(Next,s,Next);
	}
}
int block,maxblock[200],L[200],R[200],tag[200];
int date[10005],pos[10005];
inline void build()
{
	block=sqrt(n);
	for (int i=1;i<=block;i++)
	{
		L[i]=(i-1)*block+1;
		R[i]=i*block;
	}
	R[block]=n;
	for (int i=1;i<=block;i++)
	{
		for (int j=L[i];j<=R[i];j++)
		{
			pos[j]=i;
			date[j]=deep[line_to_tree[j]];
			maxblock[i]=max(maxblock[i],date[j]);
		}
	}
}
inline void change(int l,int r,int val)
{
	for (int i=pos[l];i<=pos[r];i++)
	{
		if (l<=L[i]&&R[i]<=r)
		{
			tag[i]+=val;
			maxblock[i]+=val;
		}
		else 
		{
			for (int j=L[i];j<=R[i];j++)
				date[j]+=tag[i];
			tag[i]=0;
			for (int j=max(l,L[i]);j<=min(r,R[i]);j++)
				date[j]+=val;
			maxblock[i]=0;
			for (int j=L[i];j<=R[i];j++)
				maxblock[i]=max(maxblock[i],date[j]);
		}
	}
	//for (int i=l;i<=r;i++) date[i]+=val;
}
inline int query(int l,int r)
{
	int res=0;
	for (int i=pos[l];i<=pos[r];i++)
	{
		if (l<=L[i]&&R[i]<=r)
		{
			res=max(res,maxblock[i]);
		}
		else 
		{
			for (int j=max(l,L[i]);j<=min(r,R[i]);j++)
				res=max(res,date[j]+tag[i]);
		}
	}
	//for (int i=l;i<=r;i++) res=max(res,date[i]);
	return res;
}
int ans[10005];
void dfs(int s,int fa)
{
	ans[s]=query(1,n);
	for (int e=head[s],Next;e;e=edge[e].Next)
	{
		Next=edge[e].to;
		if (Next==fa) continue;
		change(1,n,1);
		change(tree_to_line[Next],tree_to_line[Next]+size[Next]-1,-2);
		dfs(Next,s);
		change(1,n,-1);
		change(tree_to_line[Next],tree_to_line[Next]+size[Next]-1,2);
	}
}
int main()
{
	freopen("sb.in","r",stdin);
	freopen("sb.out","w",stdout);
	scanf("%d",&n);
	for (int i=1,x,y;i<n;i++)
	{
		scanf("%d %d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	deep[0]=-1;
	dfs1(1,0);
	dfs2(1,0,1);
	build();
	dfs(1,0);
	for (int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
