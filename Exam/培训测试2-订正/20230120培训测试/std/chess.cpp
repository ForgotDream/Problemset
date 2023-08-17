#include <bits/stdc++.h>
#define fo(a,b,c) for (a=b; a<=c; a++)
#define fd(a,b,c) for (a=b; a>=c; a--)
#define abs(x) ((x)>0?(x):-(x))
#define ll long long
#define file
using namespace std;

int n,m,X1,Y1,X2,Y2,ans,s1,s2,s3,s4;

int main()
{
	scanf("%d%d%d%d%d%d",&n,&m,&X1,&Y1,&X2,&Y2);
	s1=X2-1,s2=n-X2,s3=Y2-1,s4=m-Y2;
	if (abs(X1-X2)+abs(Y1-Y2)==1) ans=-1;
	else
	if (s1<=1 && s2<=1 && s3<=1 && s4<=1) ans=1;
	else
	if (n<=2 || m<=2) ans=2;
	else
	if ((s1<=1 || s2<=1) && (s3<=1 || s4<=1)) ans=2;
	else
	ans=3;
	printf("%d\n",ans);
}
