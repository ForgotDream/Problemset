#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<map>
#include<unordered_map>
using namespace std;
#define int unsigned long long 
const int MOD=998244353;
map<pair<int ,int >,int >mem;
int qc(int n,int m)
{
	if (mem[make_pair(n,m)]) return mem[make_pair(n,m)];
	else
	{
		
		if (n==m) return 1;
		if (n>m) return 0;
		return mem[make_pair(n,m)]=(qc(n,m-1)+qc(n-1,m-1))%MOD;
	}
}
int n;
int date[100005];
int cnt[2049];
int possible[13]={0,1,2,4,8,16,32,64,128,256,512,1024,2048};
int success[13]={0,2048,1024,512,256,128,64,32,16,8,4,2,1};
int pow2[100005];
unordered_map<int,int >dp;
int pre[13];
int dfs(int pos,int sum1,bool isSuccess)
{
	//if (pre[pos]+sum1<2048) return 0;
	if (pos==0) return isSuccess;
	if (dp[sum1*100+pos*10+isSuccess]) return dp[sum1*100+pos*10+isSuccess];
	int res=0;
	for (int i=0;i<=cnt[possible[pos]];i++)
		res+=dfs(pos-1,sum1+i*possible[pos],sum1>=2048||isSuccess)*qc(i,cnt[possible[pos]])%MOD,res%=MOD;
	dp[sum1*100+pos*10+isSuccess]=res%MOD;
	return res%MOD;
}
inline int solve()
{
	int res=0;
	for (int i=0;i<=cnt[possible[12]];i++)
		res+=dfs(11,i*2048,i),res%=MOD;
	return res;
}
int ans;
signed main()
{
	freopen("2048.in","r",stdin);
	freopen("2048.out","w",stdout);
	scanf("%lld",&n);
	for (int i=1;i<=n;i++)
		scanf("%lld",&date[i]);
	pow2[0]=1;
	for (int i=1;i<=n;i++)
		pow2[i]=(pow2[i-1]*2)%MOD;
	if (n<=20)
	{
		long ans=0;
		for (long i=(1<<n)-1;i>=0;i--)
		{
			for (long j=1;j<=n;j++)
				if ((i>>(j-1))&1)
					cnt[date[j]]++;
			for (long j=1;j<=11;j++)
				cnt[possible[j+1]]+=cnt[possible[j]]/2;
			if (cnt[possible[12]]) ans++,ans%=MOD;
			for (int j=1;j<=12;j++)
				cnt[possible[j]]=0;
		}
		printf("%d",ans);
		return 0;
	}
	for (int i=1;i<=n;i++)
		cnt[date[i]]++;
	int temp=0;
	for (int i=1;i<=12;i++)
		temp+=cnt[possible[i]],pre[i]=pre[i-1]+cnt[possible[i]]*possible[i];
	printf("%lld",solve()*pow2[n-temp]);
	return 0;
}
