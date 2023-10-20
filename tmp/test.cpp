#include<climits>
#include<cstdio>
#include<functional>
#include<iomanip>
#include<ios>
#include<queue>
#include<cmath>
#include<set>
#include<map>
#include<iostream>
#include<stack>
#include<string>
#include<tuple>
#include<typeindex>
#include<utility>
#include<vector>
#include<cstring>
#include<algorithm>
#include<bitset>
typedef long long ll;
typedef long double ldouble;
typedef unsigned long long ull;
const int N=(1<<20)+5;
int n,m,val[N],temp[N];
ll cnt[25][2];
inline void Merge(int l,int r,int deep)
{
	if (l>=r) return;
	int mid=(l+r)/2;
	Merge(l,mid,deep-1);
	Merge(mid+1,r,deep-1);
	int i=l,j=mid+1;
	while (i<=mid&&j<=r)
	{
		if (val[i]<val[j])
			cnt[deep][1]+=r-j+1,i++;
		else j++;
	}
	i=l,j=mid+1;
	int p=0;
	while (i<=mid&&j<=r)
	{
		if (val[i]>val[j]) cnt[deep][0]+=mid-i+1,temp[p++]=val[j++];
		else temp[p++]=val[i++];
	}
	for (;i<=mid;temp[p++]=val[i++]);
	for (;j<=r;temp[p++]=val[j++]);
	for (int i=l;i<=r;i++)
		val[i]=temp[i-l];
}
int main ()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);std::cout.tie(0);
	std::cin>>n;
	for (int i=1;i<=(1<<n);i++)
		std::cin>>val[i];
	Merge(1,1<<n,n);
	std::cin>>m;
	while (m--)
	{
		int x;
		std::cin>>x;
		ll res=0;
		for (int i=1;i<=x;i++)
			std::swap(cnt[i][0],cnt[i][1]);
		for (int i=1;i<=n;i++)
			res+=cnt[i][0];
		std::cout<<res<<'\n';
	}
	return 0;
}
