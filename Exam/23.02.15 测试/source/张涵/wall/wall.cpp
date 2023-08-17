#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<ctime>
#include<set>
#include<vector>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#define File(x) freopen(""#x".in","r",stdin)
#define Look(x) freopen(""#x"","w",stdout)
#define rep(i,l,r) for(int i=l; i<r; ++i)
#define drep(i,r,l) for(int i=r; i>l; --i)
#define vi vector<int>
#define db double
#define debug cerr<<"ok"<<endl
#define CT cout<<TNT<<':'<<"--------------------------------"<<endl
#include<unordered_map>
using namespace std;
#define int long long
int H,n;
struct POINT
{
	int x,y;
}point[1100];
vector<int>End;
vector<int>Begin;
struct EDGE
{
	int to,w,Next;
}edge[2200000];
int total,head[1100];
inline void add_edge(int u,int v,int w)
{
	edge[++total]=EDGE{v,w,head[u]};head[u]=total;
}
bool check(POINT a,POINT b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)<=1000*1000;
}
bool book[1010];
int dis[1010];
int ans=0x7f7f7f7f7f7f7f7f;
inline void spfa(int s)
{
	queue<int>q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(s);
	book[s]=true;
	int pos;
	while (!q.empty())
	{
		pos=q.front();q.pop();
		book[pos]=false;
		for (int e=head[pos],Next;e;e=edge[e].Next)
		{
			Next=edge[e].to;
			if (dis[pos]+edge[e].w<dis[Next])
			{
				dis[Next]=dis[pos]+edge[e].w;
				if (!book[Next])
				{
					book[Next]=true;
					q.push(Next);
				}
			}
		}
	}
}
signed main()
{
	freopen("wall.in","r",stdin);
	freopen("wall.out","w",stdout);
	scanf("%lld %lld",&H,&n);
	if (H<=1000) 
	{
		cout<<'0'<<endl;
		return 0;
	}
	for (int i=1;i<=n;i++)
	{
		scanf("%lld %lld",&point[i].x,&point[i].y);
		if (H-point[i].y<=1000) End.push_back(i);
		if (point[i].y<=1000) Begin.push_back(i);
	}
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			if (check(point[i],point[j]))
			{
				add_edge(i,j,1);
				add_edge(j,i,1);
			}
	for (vector<int>::iterator i=Begin.begin();i!=Begin.end();i++)
	{
		spfa(*i);
		for (vector<int>::iterator j=End.begin();j!=End.end();j++)
		{
			ans=min(dis[*j],ans);
			if (ans==1) break;
		}
	}
	printf("%lld",ans+1);
	return 0;
}
