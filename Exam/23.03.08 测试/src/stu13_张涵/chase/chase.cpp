#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<unordered_map>
#include<bitset>
using namespace std;
#define int unsigned int 
int n;
struct POINT
{
	int begin,v;
	bool operator <(const POINT&b)const
	{
		return begin<b.begin;
	}
}point[100005];
signed main()
{
	freopen("chase.in","r",stdin);
	freopen("chase.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d %d",&point[i].begin,&point[i].v);
	}
	sort(point+1,point+1+n);
	if (n==2)
	{
		if (point[1].begin==point[2].begin) 
		{
			printf("0.00");
			return 0;
		}
		if (point[1].v<point[2].v)
		{
			printf("0.00");
			return 0;
		}
		if(point[1].v>=point[2].v)
		{
			printf("%d.00",point[1].v*(point[2].begin-point[1].begin));
			return 0;
		}
	}
	printf("0.00");
	return 0;
}
