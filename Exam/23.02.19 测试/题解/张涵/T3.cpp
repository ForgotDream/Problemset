#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
int n,low,hi,len[1100],magic[1100];
int prelen[1100],premagic[1100];
struct RANGE
{
	int x,y;
	int val;
	bool operator <(const RANGE&b) const 
	{
		if(x==b.x) return y>b.y;
		return x<b.x;
	}
}seg[1100*1100];
int total,ans,dp[1100];
signed main()
{
	cin>>n>>low>>hi;
	for(int i=1;i<=n;i++) cin>>len[i],prelen[i]=prelen[i-1]+len[i];
	for(int i=1;i<=n;i++) cin>>magic[i],premagic[i]=premagic[i-1]+magic[i];
	for(int l=1;l<=n;l++) 
		for(int r=l;r<=n;r++) 
			if(low<=prelen[r]-prelen[l-1]&&prelen[r]-prelen[l-1]<=hi) 
			{
				seg[++total].x=l;
				seg[total].y=r;
				seg[total].val=premagic[r]-premagic[l-1];
			}
	sort(seg+1,seg+1+total);
    //这个sort很重要，没了他正确性就没了
    //先按照 x 的升序，x相同再 y 的降序排列
    //正确性证明如下
    //1.如果seg[i].x>seg[i-1].x
    //  此时显然不会有冲突
    //2.如果seg[i].x==seg[i-1].x
    //  如果dp没有被更新，显然没有问题
    //  如果被
	for(int i=1;i<=total;i++)
		for(int j=1;j<seg[i].y;j++)
			dp[seg[i].y]=max(dp[seg[i].y],dp[j]+seg[i].val);
	if(total==1) {cout<<seg[1].val; return 0;}
    //这里是防止一下特殊情况
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	cout<<ans;
	return 0;
}