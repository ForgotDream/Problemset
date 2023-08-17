#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<iostream>
#include<unordered_map>
//#define int long long 
using namespace std;
int n;
int hi[100005];
int top,stk[100005],w[100005];
int ans;
int main()
{
	freopen("england.in","r",stdin);
	freopen("england.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&hi[i]);
	stk[++top]=0;
	w[top]=1;
	for (int i=1;i<=n+1;i++)
	{
		if (hi[i]>stk[top])
		{
			stk[++top]=hi[i];
			w[top]=1;
		}
		else
		{
			int width=0;
			while(stk[top]>hi[i])
			{
				width+=w[top];
				ans=max(ans,width*stk[top]);
				top--;
			}
			stk[++top]=hi[i];
			w[top]=width+1;
		}
	}
	printf("%d",ans);
	return 0;
}
