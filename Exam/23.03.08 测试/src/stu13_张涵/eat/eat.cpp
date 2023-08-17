#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<unordered_map>
#include<bitset>
using namespace std;
#define int unsigned long long 
int n,cnt[5];
int dp[10000000];
int dp2[10000000];
int pre[10000000];
int last,MM=2147483647;
signed main()
{
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
	scanf("%lld %lld %lld %lld %lld",&n,&cnt[1],&cnt[2],&cnt[3],&cnt[4]);
	for (int i=1,x;i<=cnt[1];i++)
	{
		scanf("%lld",&x);
		MM=min(MM,x);
		dp[x]++;
	}
	last=MM;
	for (int i=MM;i<=n;i++)
		dp[i]=dp[i-1]+dp[i];
	for (int i=2;i<=4;i++)
	{
		MM=2147483647;
		for (int j=1;j<=n;j++)
			dp2[j]=dp[j],dp[j]=0 /*,pre[j]=dp2[j]+dp2[j-1]*/;
		for(int j=1,x;j<=cnt[i];j++)
		{
			scanf("%lld",&x);
			if (x+last>n) continue;
			MM=min(MM,x);
			//dp[k]+=pre[n-x]-pre[last-1];
			for (int k=x+last;k<=n;k++)
				dp[k]+=dp2[k-x];
			//pre[x+last]++;
		}
		//for (int j=1;j<=last;j++) pre[x]=pre[x-1]+pre[x];
		last+=MM;
	}
	printf("%lld",dp[n]);
	return 0;
}
/*
11 3 1 1 1
4 5 6
3
2
1
*/
