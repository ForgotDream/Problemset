#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
#include<unordered_map>
#include<stack>
#include<queue>
#include<ctime>
using namespace std;
int n;
int X[10000];
bool CMP(int a,int b)
{
	return a>b;
}
int sumzero;
int presum[10000],fpresum[10000];
int ans;
int zerostk;
inline bool check(int sumstk)
{
	int stk[5005],res[5005];
	memset(stk,0,sizeof(stk));
	memset(res,0,sizeof(res));
	for (int i=1;i<=sumstk;i++)
	{
		stk[i]=X[i];
		res[i]=X[i];
	}
	bool flag;
	for (int i=sumstk+1,pos;i<=n;i++)
	{
		flag=false;pos=1;
		for (int j=1;j<=sumstk;j++)
		{
			if(res[j]&&stk[j]>X[i]&&res[j]>res[pos])
			{
				pos=j;
				/*stk[j]=X[i];
				res[j]=min(res[j]-1,X[i]);*/
				flag=true;
				break;
			}
		}
		if (flag)
		{
			stk[pos]=X[i];
			res[pos]=min(res[pos]-1,X[i]);
			continue;
		}
		for (int j=1;j<=sumstk;j++)
		{
			if (res[j])
			{
				stk[j]=X[i];
				res[j]=min(res[j]-1,X[i]);
				flag=true;
				break;
			}
		}
		if (flag) continue;
		else return false;
	}
	return true;
}
int l,r;
int main()
{
	freopen("box.in","r",stdin);
	freopen("box.out","w",stdout);
	scanf("%d",&n);
	ans=n;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&X[i]);
		if (!X[i]) sumzero++;
	}
	/*if (sumzero>=n-sumzero)
	{
		printf("%d",sumzero);
		return 0;
	}*/
	sort(X+1,X+1+n,CMP);
	l=max(1,sumzero);
	r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d",l);
	return 0;
}
/*
1 1 4 5 1 4 1 9 1 9
1 1 1 1 1 4 4 5 9 9
1
1 1
4 1
5 4 
9 9 1
*/
