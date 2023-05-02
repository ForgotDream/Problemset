#include<climits>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
#include <type_traits>
using namespace std;
typedef long long ll;
typedef long double ldouble ;
bool dis[205][205];
int Link[205];
bool vis[205],isDel[205];
int N,M;
bool Match(int x)
{
	if (x==0) return true;
	for (int y=1;y<=N;y++)
		if (dis[x][y]&&(!vis[y]))
		{
			if (isDel[y]) continue;
			vis[y]=true;
			if (!Link[y]||Match(Link[y]))
			{
				Link[y]=x;
				return true;
			}
		}
	return false;
}
bool isAble[205];
bool isChoose[205];
int col[205];
int main()
{
	cin>>N>>M;
	for (int i=1,x,y;i<=M;i++)
	{
		cin>>x>>y;
		dis[x][y]=true;
	}
	for (int k=1;k<=N;k++)
		for (int i=1;i<=N;i++)
			for (int j=1;j<=N;j++)
				if (dis[i][k]&&dis[k][j])
					dis[i][j]=true;
	int sumMatch=0;
	for (int i=1;i<=N;i++)
	{
		memset(vis,false,sizeof(vis));
		if (Match(i)) sumMatch++;
	}
	for (int root=1,sumMatch2,n2;root<=N;root++)
	{
		memset(isDel,false,sizeof(isDel));
		memset(Link,0,sizeof(Link));
		n2=N, sumMatch2=0;
		for (int i=1;i<=N;i++)
			if (dis[i][root]||dis[root][i]||i==root)
				isDel[i]=true,n2--;
		for (int i=1;i<=N;i++)
		{
			if (isDel[i]) continue;
			memset(vis,false,sizeof(vis));
			if (Match(i)) sumMatch2++;
		}
		if (n2-sumMatch2==N-sumMatch-1) isAble[root]=true;
	}
	int Color=0;
	for (int i=1;i<=N;i++)
	{
		if (isAble[i]&&(!col[i]))
		{
			Color++;
			isChoose[i]=true;
			for (int j=1;j<=N;j++)
				if (dis[i][j]||dis[j][i]||j==i)
					col[j]=Color;
		}
	}
	cout<<N-sumMatch<<'\n';
	for (int i=1;i<=N;i++)
		cout<<isChoose[i];
	cout<<'\n';
	for (int i=1;i<=N;i++)
		cout<<isAble[i];
	return 0;
}