#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
#include<unordered_map>
#include<stack>
#include<queue>
#include<ctime>
using namespace std;
#define int unsigned long long
const int MOD=1000000007;
int n,k,ans;
int p[9];
inline bool check()
{
	for (int i=1,pos,cnt;i<=k;i++)
	{
		pos=i;
		cnt=0;
		while(pos!=1)
		{
			pos=p[pos];
			cnt++;
			if (cnt>k) return false;
		}
	}
	return true;
}
void dfs(int step)
{
	if (step==k+1)
	{
		if (check()) ans++;
		return ;
	}
	int L,R;
	L=1;
	R=k;
	for (int i=L;i<=R;i++)
	{
		p[step]=i;
		dfs(step+1);
	}
}
inline int qsm(int a,int b)
{
	int base=a;
	a=1;
	base%=MOD;
	while (b)
	{
		if (b&1)
		{
			a=(a*base)%MOD;
			b--;
		}
		else
		{
			base=(base*base)%MOD;
			b>>=1;
		}
	}
	return a;
}
int temp;
signed main()
{
	freopen("castle.in","r",stdin);
	freopen("castle.out","w",stdout);
	scanf("%lld %lld",&n,&k);
	dfs(1);
	temp=qsm(n-k,n-k);
	ans=ans*temp%MOD;
	printf("%lld",ans);
	return 0;
}
/*
1000000000000000000 6
*/
