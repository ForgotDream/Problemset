#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int R()
{
	int x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(48^c),c=getchar();
	return x;
}
const int MAXN=1009;
int n,m;
int a[MAXN][MAXN],s[MAXN][MAXN];
int F[MAXN];
int main()
{
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	n=R(),m=R();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=R();
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			if(a[i][j])F[j]=0;
			else F[j]++;
		for(int j=1;j<=m;j++)
		{
			if(!F[j])continue;
			int l=j,r=j;
			while(F[l-1]>=F[j])l--;
			while(F[r+1]>=F[j])r++;
			ans=max(ans,(r-l+1)*F[j]);
		}
	}
	printf("%d",ans);
	return 0;
}
