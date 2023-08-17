#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<ctime>
#include<set>
#include<vector>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#define File(x) freopen(""#x".in","r",stdin)
#define Look(x) freopen(""#x"","w",stdout)
#define rep(i,l,r) for(int i=l; i<r; ++i)
#define drep(i,r,l) for(int i=r; i>l; --i)
#define vi vector<int>
#define db double
#define debug cerr<<"ok"<<endl
#define CT cout<<TNT<<':'<<"--------------------------------"<<endl
#include<unordered_map>
using namespace std;
#define int long long 
int num[30],len;
int dp[20][20][2][2][2];//dp[pos][pre][isBegin][isFour][isThirteen]
int dfs(int pos,int pre,bool isBegin,bool isFour,bool isThirteen,bool isSmall)
{
	if (pos<=0)
	{
		return isBegin&&(isFour||isThirteen);
	}
	if (isSmall&&dp[pos][pre][isBegin][isFour][isThirteen]!=-1)
		return dp[pos][pre][isBegin][isFour][isThirteen];
	int MM=isSmall?9:num[pos],res=0;
	for (int i=0;i<=MM;i++)
	{
		res+=dfs(pos-1,i,isBegin||i!=0,isFour||i==4,isThirteen||(pre==1&&i==3),isSmall||i<MM);
	}
	if (isSmall) dp[pos][pre][isBegin][isFour][isThirteen]=res;
	return res;
}
inline int solve(int date)
{
	len=0;
	while (date)
	{
		num[++len]=date%10;
		date/=10;
	}
	int sum=0;
	for (int i=0;i<=num[len];i++)
	{
		sum+=dfs(len-1,i,i!=0,i==4,false,i<num[len]);
	}
	return sum;
}
int T,k,h;
signed main()
{
	freopen("height.in","r",stdin);
	freopen("height.out","w",stdout);
	memset(dp,-1,sizeof(dp));
	scanf("%lld",&T);
	while (T--)
	{
		scanf("%lld %lld",&k,&h);
		printf("%lld\n",(k-solve(k))*h);
	}
	return 0;
}
/*
69710524626
*/
/*
267595583202 361948
17473019847
69710524626
17473019847

6324324587581956

37239247665066447
*/
