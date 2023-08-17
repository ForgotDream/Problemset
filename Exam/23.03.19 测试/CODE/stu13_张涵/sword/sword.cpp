#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
#define int long long
int a,b,T,ans;
inline int gcd(int a,int b)
{
	if (a<b) swap(a,b);
	if (b==0) return a;
	else
	{
		ans+=(a-b)/b;
		if (((a-b)/b)*b!=a-b) ans++;
		return gcd(a%b,b);
	}
	
}
signed main()
{
	freopen("sword.in","r",stdin);
	freopen("sword.out","w",stdout);
	scanf("%lld",&T);
	while (T--)
	{
		ans=0;
		scanf("%lld %lld",&a,&b);
		if (a==b)
		{
			printf("0\n");
			continue;
		}
		gcd(a,b);
		printf("%lld\n",ans);
	}
	return 0;
}
/*
¨¢?????¨ºy a¡ê?b
???¡ä¨°???2¨´¡Á¡Â?¡À¦Ì?a=b 
?¨´¨¦¨¨ a>b
a=a-b,b=b; 
*/
