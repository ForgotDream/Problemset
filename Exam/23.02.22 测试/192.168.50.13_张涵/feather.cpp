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
using namespace std;
#define ll long long 
long long n,m,k,T;
long long pointnum[1000050];
long long l,r=0x7f7f7f7f;
inline bool check(long long mid)
{
	long long sum=mid;
	long long rest=0;
	rest+=sum;
	rest-=pointnum[1];
	if (rest<0) return false;
	rest+=0;
	rest-=pointnum[2];
	if (rest<0) return false;
	for (int i=3;i<=n;i++)
	{
		rest+=pointnum[i-2];
		rest-=pointnum[i];
		if (rest<0) return false;
	}
	rest-=pointnum[1];
	if (rest<0) return false;
	return true;
}
int main()
{
	freopen("feather.in","r",stdin);
	freopen("feather.out","w",stdout);
	scanf("%lld",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%lld",&pointnum[i]);
	}
	if (n==2)
	{
		printf("%lld",pointnum[1]+pointnum[2]);
		return 0;
	}
	if (n==1)
	{
		printf("%lld",pointnum[1]);
		return 0;
	}
	long long mid;
	r=0x7f7f7f7f;
	while (l<r)
	{
		mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%lld",l);
	return 0;
}
/*
ans  0->
		2 2 1 1 2 2 1 1
rest 0->	
*/
