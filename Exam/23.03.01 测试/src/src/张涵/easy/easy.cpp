#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
struct NODE
{
	int l,r;
	mutable int v;
	bool operator <(const NODE &b)const
	{
		return l<b.l;
	}
};
int Map[1100][1100];
int presum[1100][1100];
int n,m;
int stk[2000],w[2000],top;
int main()
{
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			cin>>Map[i][j];
			Map[i][j]=Map[i][j]==0?1:0;
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			if (Map[i][j]) presum[i][j]=presum[i-1][j]+Map[i][j];
			else presum[i][j]=0;
		}
	int ans=0;
	for (int i=1;i<=n;i++)
	{
		top=0;
		for (int j=1;j<=m+1;j++)
		{
			if (presum[i][j]>stk[top])
			{
				stk[++top]=presum[i][j],w[top]=1;
			}
			else
			{
				int width=0;
				while (stk[top]>presum[i][j]&&top)
				{
					width+=w[top];
					ans=max(ans,width*stk[top]);
					top--;
				}
				stk[++top]=presum[i][j];w[top]=width+1;
			}
		}
	}
	cout<<ans;
	return 0;
}
