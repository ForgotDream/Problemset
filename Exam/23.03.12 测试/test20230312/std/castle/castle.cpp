#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define p 1000000007
#define ll long long
ll n,k,ans;
ll POW(ll a,ll k)
{
	if (k==0) return 1;
	ll tmp=POW(a,k>>1)%p;tmp=tmp*tmp%p;
	if (k&1) return tmp*a%p;else return tmp;
}
int main()
{
	freopen("castle.in","r",stdin);
	freopen("castle.out","w",stdout);
	cin>>n>>k;
	ans=POW(k,k-1)*POW((n-k)%p,n-k)%p;
	cout<<ans;
	fclose(stdin);fclose(stdout);
}
