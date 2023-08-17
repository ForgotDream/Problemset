#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<iostream>
#include<unordered_map>
#include<queue>
//#define int long long 
#define ll long long
#define ull unsigned long long 
#define ldouble long double
using namespace std;
int pre[105];
int Map[105][105][105];
int dp[105][105][105];
struct Way
{
	int toX,toY,toF;
	int Next;
	int Time;
}way[2000000];
int head[338350+100],total;
int n,m;
inline int qid(int x,int y,int Floor)
{
	return pre[Floor-1]+x*(n-Floor+1)+y;
}
int Nx[4]={0,0,1,1};
int Ny[4]={0,1,0,1};
int ans=2147483647;
int main()
{
	freopen("egypt.in","r",stdin);
	freopen("egypt.out","w",stdout);
	memset(dp,0x3f,sizeof(dp));
	/*for (int i=1;i<=100;i++)
		pre[i]=i*i;
	for (int i=1;i<=100;i++)
		pre[i]=pre[i-1]+pre[i];*/
	scanf("%d %d",&n,&m);
	for (int i=1;i<=n;i++)
		pre[i]=(n-i+1)*(n-i+1);
	for (int i=1;i<=n;i++)
		pre[i]=pre[i]+pre[i-1];
	for (int f=1;f<=n;f++)
		for (int i=1;i<=n-f+1;i++)
			for (int j=1;j<=n-f+1;j++)
				scanf("%d",&Map[i][j][f]);
	for (int i=1,a1,b1,c1,a2,b2,c2,p;i<=m;i++)
	{
		total++;
		scanf("%d %d %d %d %d %d %d"
			,&way[total].toF,&way[total].toX,&way[total].toY
			,&a1,&b1,&c1
			,&way[total].Time
		);
		way[total].Next=head[qid(b1,c1,a1)];
		head[qid(b1,c1,a1)]=total;
	}
	//dp[1][1][n]=Map[1][1][n];
	dp[1][1][n]=0;
	for (int f=n;f>=1;f--)
	{
		for (int i=1;i<=n-f+1;i++)
			for (int j=1;j<=n-f+1;j++)
			{
				if (1<=i-1&&1<=j-1) 
					dp[i][j][f]=min(dp[i][j][f],dp[i-1][j-1][f+1]+Map[i-1][j-1][f+1]);
				if (1<=i-1&&j!=n-f+1)
					dp[i][j][f]=min(dp[i][j][f],dp[i-1][j][f+1]+Map[i-1][j][f+1]);
				if (i!=n-f+1&&1<=j-1)
					dp[i][j][f]=min(dp[i][j][f],dp[i][j-1][f+1]+Map[i][j-1][f+1]);
				if (i<n-f+1&&j<n-f+1)
					dp[i][j][f]=min(dp[i][j][f],dp[i][j][f+1]+Map[i][j][f+1]);
			}
		for (int i=1;i<=n-f+1;i++)
			for (int j=1;j<=n-f+1;j++)
			{
				if (i!=1) dp[i][j][f]=min(dp[i][j][f],dp[i-1][j][f]+Map[i][j][f]);
				if (j!=1) dp[i][j][f]=min(dp[i][j][f],dp[i][j-1][f]+Map[i][j][f]);
				if (i!=n-f+1) dp[i][j][f]=min(dp[i][j][f],dp[i+1][j][f]+Map[i][j][f]);
				if (j!=n-f+1) dp[i][j][f]=min(dp[i][j][f],dp[i][j+1][f]+Map[i][j][f]);
			}
		for (int i=n-f+1;i>=1;i--)
			for (int j=n-f+1;j>=1;j--)
			{
				if (i!=1) dp[i][j][f]=min(dp[i][j][f],dp[i-1][j][f]+Map[i][j][f]);
				if (j!=1) dp[i][j][f]=min(dp[i][j][f],dp[i][j-1][f]+Map[i][j][f]);
				if (i!=n-f+1) dp[i][j][f]=min(dp[i][j][f],dp[i+1][j][f]+Map[i][j][f]);
				if (j!=n-f+1) dp[i][j][f]=min(dp[i][j][f],dp[i][j+1][f]+Map[i][j][f]);
			}
		for (int i=1;i<=n-f+1;i++)
			for (int j=1;j<=n-f+1;j++)
			{
				for (int e=head[qid(i,j,f)];e;e=way[e].Next)
				{
					dp[way[e].toX][way[e].toY][way[e].toF]=min(
						dp[way[e].toX][way[e].toY][way[e].toF],
						dp[i][j][f]+way[e].Time+Map[way[e].toX][way[e].toY][way[e].toF]
					);
				}
			}
		/*for (int i=1;i<=n-f+1;i++)
		{
			for (int j=1;j<=n-f+1;j++)
				printf("%d ",dp[i][j][f]);
			putchar('\n');	
		}
		putchar('\n');	*/
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			ans=min(ans,dp[i][j][1]+abs(i-1)+abs(j-1));
	printf("%d",ans+Map[1][1][1]);
	return 0;
}
/*
4 2
4 1 5 2
4 3 4 7
1 9 2 8
0 3 5 1
2 8 5
9 3 9
1 1 8
7 4
5 2
42
1 1 2 2 3 1 1
1 3 2 2 2 1 7
*/
