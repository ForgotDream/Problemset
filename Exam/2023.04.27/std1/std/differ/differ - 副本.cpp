#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long  LL;
const int N=505;
int m,n,q;
LL a[N][N];

void work()
{
	scanf("%d %d",&m,&n);
	for (int i=1; i<=m; i++)
		for (int j=1; j<=m; j++)
			a[i][j]=(LL)(i!=j)<<60;
	for (int i=1,t,x,y,w; i<=n; i++)
	{
		scanf("%d %d %d %d",&t,&x,&y,&w);
		if (t==0)  a[y][x]=min(a[y][x],(LL)w);
		else  if (t==1)  a[x][y]=min(a[x][y],(LL)-w);
		else
		{
			a[y][x]=min(a[y][x],(LL)w);
			a[x][y]=min(a[x][y],(LL)-w);
		}
	}
	for (int k=1; k<=m; k++)
		for (int i=1; i<=m; i++)
			for (int j=1; j<=m; j++)
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
	scanf("%d",&q);
	for (int i=1,x,y; i<=q; i++)
	{
		scanf("%d %d",&x,&y);
		if (a[y][x]>=1LL<<59)  puts("Infinity");
		else  printf("%lld\n",a[y][x]);
	}
}

int main()
{
	freopen("differ.in","r",stdin);
	freopen("differ.out","w",stdout);
	work();
	return 0;
}
