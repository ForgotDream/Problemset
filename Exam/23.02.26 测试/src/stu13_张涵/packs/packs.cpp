#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<cmath>
#include<unordered_map>
#include<set>
#include<bitset>
#include<queue>
using namespace std;
priority_queue<int>q; 
int n,m;
int sumn,summ;
int notebook[10000],pen[10000];
int dp1[2000000],dp2[2000000];
int main()
{
	freopen("packs.in","r",stdin);
	freopen("packs.out","w",stdout);
	memset(dp1,0x3f,sizeof(dp1)); 
	dp1[0]=0;
	memset(dp2,0x3f,sizeof(dp2));
	dp2[0]=0;
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>notebook[i],sumn+=notebook[i];
	sort(notebook+1,notebook+1+n); 
	for (int i=1;i<=n;i++)
	{
		for (int j=sumn;j>=notebook[i];j--)
		{
			if (dp1[j-notebook[i]]!=0x3f3f3f3f)
			{
				dp1[j]=min(dp1[j],dp1[j-notebook[i]]+1);
			}
		}
	}
	cin>>m;
	for (int i=1;i<=m;i++)
		cin>>pen[i],summ+=pen[i];
	sort(pen+1,pen+1+m); 
	for (int i=1;i<=m;i++)
	{
		for (int j=summ;j>=pen[i];j--)
		{
			if (dp2[j-pen[i]]!=0x3f3f3f3f)
			{
				dp2[j]=min(dp2[j],dp2[j-pen[i]]+1);
			}
		}
	}
	int ans=0x3f3f3f3f;
	for (int i=1;i<=min(summ,sumn);i++)
	{
		if (dp1[i]!=0x3f3f3f3f&&dp2[i]!=0x3f3f3f3f)
		{
			ans=min(dp1[i]+dp2[i],ans);
		}
	}
	if (ans==0x3f3f3f3f)
	{
		cout<<"impossible";
	}
	else 
	{
		cout<<ans;
	}
	return 0;
}
/*
给你两个序列
各从其中抽取几个数，使得两个序列选出的数和相等
使选的数的个数最小 
考虑背包问题
每个物品 
*/
