#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
#define int unsigned long long 
int dp[50][50];//dp[pos][sumone]
int n,l,I;
int num[50],len;
int L,R;
inline int dfs(int pos,int sumone,bool isSmall)
{
	if (pos==0) return sumone<=l;
	if (sumone>l) return 0;
	if (isSmall&&dp[pos][sumone]!=-1) return dp[pos][sumone];
	int MM=isSmall?1:num[pos],res=0;
	for (int i=0;i<=MM;i++)
	{
		res+=dfs(pos-1,sumone+i,isSmall||i<num[pos]);
	}
	if (isSmall) dp[pos][sumone]=res;
	return res;
}
inline int solve(int date)
{
	len=0;
	while (date)
	{
		num[++len]=date%2;
		date/=2;
	}
	int res=0;
	for (int i=0;i<=num[len];i++)
		res+=dfs(len-1,i,i<num[len]);
	return res;
}
signed main()
{
	memset(dp,-1,sizeof(dp));
	freopen("bits.in","r",stdin);
	freopen("bits.out","w",stdout);
	cin>>n>>l>>I;
	R=1;
	R<<=32;
	L=0;
	int mid;
	while (L<R)
	{
		mid=(L+R+1)>>1;
		if (solve(mid)>I) R=mid-1;
		else L=mid;
	}
	len=0;
	memset(num,0,sizeof(num));
	len=0;
	while (L)
	{
		num[++len]=L%2;
		L/=2;
	}
	for (int i=n;i>=1;i--)
	{
		printf("%d",num[i]);
	}
	/*cin>>n>>l;
	cout<<solve(19);*/
	/*12937008*/
	return 0;
}
