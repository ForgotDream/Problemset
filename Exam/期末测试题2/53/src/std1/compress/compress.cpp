#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 3010
#define INF 0x3f3f3f3f
int dp[MAXN][MAXN*2];
int mat[MAXN][MAXN*2];

int nextInt() {
	int ans=0;
	char c = 0;
	while (c=getchar(),c<'0'||c>'9');
	while (ans = ans*10+c-'0',c=getchar(),c>='0' && c<='9');
	return ans;
}

int main() {
	freopen("compress.in","r",stdin);
	freopen("compress.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	memset(mat,0x3f,sizeof(mat));
	memset(dp,0x3f,sizeof(dp));
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			int x;
			x = nextInt();
			//scanf("%d",&x);
			mat[i][j] = mat[i][j+m] = x;
		}
	for (int j=1;j<=m;j++)
		dp[0][j] = 0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m*2;j++)
			dp[i][j] = min(dp[i-1][j-1],min(dp[i-1][j],dp[i-1][j+1])) + mat[i][j];
	int ans = INF;
	for (int j=1;j<=m*2;j++)
		ans = min(ans,dp[n][j]);
	printf("%d\n",ans);
	return 0;
}
