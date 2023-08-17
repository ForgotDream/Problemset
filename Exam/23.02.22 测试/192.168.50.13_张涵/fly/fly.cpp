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
#define File(x) freopen(""#x".in","r",stdin)
#define Look(x) freopen(""#x"","w",stdout)
#define rep(i,l,r) for(int i=l; i<r; ++i)
#define drep(i,r,l) for(int i=r; i>l; --i)
#define vi vector<int>
#define db double
#define debug cerr<<"ok"<<endl
#define CT cout<<TNT<<':'<<"--------------------------------"<<endl
using namespace std;
#define ll long long 
int n,m,k;
vector<int> date[100005];
//int date[1100];
int dp[100005];
int len;
struct POINT
{
	int x,y;
}way[1100];
bool CMP(POINT a,POINT b)
{
	if (a.x!=b.x) return a.x<b.x;	
	return a.y>b.y;
}
int main()
{
	freopen("fly.in","r",stdin);
	freopen("fly.out","w",stdout);
	memset(dp,0x3f,sizeof(dp));
	//cin>>n>>m>>k;
	scanf("%d %d %d",&n,&m,&k);
	for (int i=1,x,y;i<=k;i++)
	{
		//cin>>x>>y;
		scanf("%d %d",&x,&y);
		way[i].x=x;
		way[i].y=y;
	}
	sort(way+1,way+1+k,CMP);
	int pre=-1;
	int cnt=0;
	for (int i=1;i<=k;i++)//离散化 
	{
		if (way[i].x==pre) way[i].x=cnt;
		else 
		{
			way[i].x=++cnt;
			pre=way[i].x;
		}
	}
	for(int i=1;i<=k;i++)
	{
		date[way[i].x].push_back(way[i].y);
		//date[way[i].x]=(way[i].y);
	}
	for (int i=1,pos;i<=cnt;i++)
	{
		for (int j=0;j<date[i].size();j++)
		{
			pos=lower_bound(dp+1,dp+1+k,date[i][j])-dp;
			dp[pos]=date[i][j];
			len=max(len,pos);	
		}
	}
	long double ans=(n+m)*100;
	ans=ans-len*100*2+(len*1.4142135623730950488016887242097*100);
	long long Ans1=floor(ans),Ans2=ceil(ans);
	if (ans-Ans1<Ans2-ans) printf("%lld",Ans1);//cout<<Ans1;
	else printf("%lld",Ans2);//cout<<Ans2;
	return 0;
}
/*
考虑LIS
转化为
给你一段序列，序列上的某个值可能有多个取值，请问这玩意的最长上升子序列是多长 
*/
