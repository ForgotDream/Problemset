#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<iostream>
#include<unordered_map>
//#define int long long 
#define ll long long
#define ull unsigned long long 
#define ldouble long double
using namespace std;
struct POINT
{
	int x,y;
}enemy[200],fri[310],door;
inline ldouble qdis(POINT a,POINT b)
{
	return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline bool check_isSameline(POINT a,POINT b,POINT c)
{
	int x1=a.x,x2=b.x,x3=c.x,y1=a.y,y2=b.y,y3=c.y;
	return ((y1-y2)*(x3-x2)==(x1-x2)*(y3-y2))&&
		   ((y3-y2)*(x3-x1)==(x3-x2)*(y3-y1));
}
ldouble dis[310][310];
int n,m,x0,y0;
inline void debug()
{
	for (int i=1;i<=n+1;i++)
	{
		for (int j=1;j<=n+1;j++)
			printf("%.0Lf ",dis[i][j]);
		putchar('\n');	
	}
}
int main()
{
	freopen("brazil.in","r",stdin);
	freopen("brazil.out","w",stdout);
	scanf("%d %d %d %d",&x0,&y0,&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			dis[i][j]=1e18;
	for (int i=1;i<=n;i++)
		dis[i][i]=0;
	door.x=x0;door.y=y0;
	for (int i=1;i<=n;i++)
		scanf("%d %d",&fri[i].x,&fri[i].y);
	for(int i=1;i<=m;i++)
		scanf("%d %d",&enemy[i].x,&enemy[i].y);
	bool flag;
	for (int i=1;i<=n;i++) 
	{
		for (int j=i+1;j<=n;j++)
		{
			flag=true;
			for (int k=1;k<=m;k++)
				if (check_isSameline(fri[i],fri[j],enemy[k]))
				{
					flag=false;
					break;
				}
			if (flag)
			{
				dis[i][j]=dis[j][i]=qdis(fri[i],fri[j]);
			}
		}
		dis[i][n+1]=qdis(fri[i],door)*2;
	}
	//debug();
	for (int k=1;k<=n+1;k++)
		for(int i=1;i<=n+1;i++)
			for (int j=1;j<=n+1;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	printf("%.0Lf",dis[1][n+1]);
	return 0;
}
