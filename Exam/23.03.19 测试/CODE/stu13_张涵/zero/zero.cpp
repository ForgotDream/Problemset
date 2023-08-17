#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
int n;
int A[300],B[300],C[300],D[300],E[300];
int ABC[8000005],totABC,DE[40005],totDE;
int l,r;
int main()
{
	freopen("zero.in","r",stdin);
	freopen("zero.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&B[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&C[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&D[i]);
	for (int i=1;i<=n;i++)
		scanf("%d",&E[i]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
				ABC[++totABC]=A[i]+B[j]+E[k];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			DE[++totDE]=D[i]+E[j];
	sort(ABC+1,ABC+1+totABC);
	sort(DE+1,DE+1+totDE);
	bool flag=false;
	l=1;r=totABC;
	for (l=1;l<=totDE;l++)
	{
		while (ABC[r]+DE[l]>0&&r) r--;
		if (r==0) break;
		if (ABC[r]+DE[l]==0)
		{
			flag=true;
			break;
		}
	}
	if(flag) printf("YES");
	else printf("NO");
	return 0;
}
