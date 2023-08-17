#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
int n,m,k;
double Map[1100][1100],w;
int way[110][2100];
int temp[110];
bool CMP(int a,int b)
{
	return way[a][0]<way[b][0];
}
char Read[1000000];
int pos;
inline void scan(int &x)
{
	x=0;
	while (Read[pos]<'0'||Read[pos]>'9') pos++;
	while ('0'<=Read[pos]&&Read[pos]<='9')
	{
		x=x*10+Read[pos]-48;
		pos++;
	}
}
int main()
{
	freopen("compare.in","r",stdin);
	freopen("compare.out","w",stdout);
	scanf("%d %d %d",&n,&m,&k);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			Map[i][j]=214748364700000000;
	for (int i=1;i<=n;i++)
		Map[i][i]=0;
	for (int i=1,x,y;i<=m;i++)
	{
		scanf("%d %d %lf",&x,&y,&w);
		Map[x][y]=Map[y][x]=min(Map[x][y],w);
	}
	char c=getchar();
	int tot=0;
	for (int i=1;i<=k;i++)
	{
		pos=0;
		Read[pos]=getchar();
		while (Read[pos]!='\n')
		{
			Read[++pos]=getchar();
		}
		if (Read[0]=='I') continue;
		pos=0;
		tot++;
		while (Read[pos]!='\n')
			scan(way[tot][++way[tot][0]]);
		temp[tot]=tot;
	}
	sort(temp+1,temp+1+tot,CMP);
	double ans=214748364700000000,tt;
	bool flag;
	for (int i=1,s;i<=k;i++)
	{
		tt=0.0;flag=true;
		pos=way[temp[i]][1];
		for (int j=2;j<=way[temp[i]][0];j++)
		{
			if (Map[pos][way[temp[i]][j]]==214748364700000000) {flag=false;break;}
			tt+=Map[pos][way[temp[i]][j]];
			pos=way[temp[i]][j];
		}
		if (flag) ans=min(ans,tt);
	}
	if (ans!=214748364700000000) printf("%.4lf",ans);
	else printf("Wrong");
	return 0;
}
