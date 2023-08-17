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
int n,a[20005],ans,tot;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		ans=max(ans,a[i]+a[i-1]);
		tot+=a[i];
	}
	ans=max(ans,a[1]+a[n]);
	ans=max(ans,(tot+(n/2)-1)/(n/2));
	printf("%d",ans);
	return 0;
}