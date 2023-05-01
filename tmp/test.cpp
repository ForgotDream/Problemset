#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[18][30][19][13][11],f[4]={2,3,5,7},k[4]={0,0,0,0},st,ed,ans;
int zt[10][4]={{0,0,0,0},{0,0,0,0},{1,0,0,0},{0,1,0,0},{2,0,0,0},{0,0,1,0},{1,1,0,0},{0,0,0,1},{3,0,0,0},{0,2,0,0}};
int getsum(int sum,int a,int Max,int st,int ed) 
{
   int b=a+Max-1,size=0,num=0;Max/=10;
   
   std::cout << sum << " " << a << " " << b << " " << Max << "\n";

   if(a>ed||b<st) return 0;
   if(a>=st&&b<=ed) size=1;
   if(sum==18) return !k[0]&&!k[1]&&!k[2]&&!k[3];
   if(size&&dp[sum][k[0]][k[1]][k[2]][k[3]]>=0)
      return dp[sum][k[0]][k[1]][k[2]][k[3]];   
   for(int l=(a!=0);l<=9;l++) 
   {
      int F=1;
      for(int i=0;i<4;i++)F&=zt[l][i]<=k[i];
      if(!F) continue;
      for(int i=0;i<4;i++)k[i]-=zt[l][i];
      num+=getsum(sum+1,a+l*Max,Max,st,ed);
      for(int i=0;i<4;i++)k[i]+=zt[l][i];
	}
   if(size) dp[sum][k[0]][k[1]][k[2]][k[3]]=num;
   return num;
}
void solve(int Max,int sum,int num) 
{
	if(sum>1000000000||sum*sum>Max)return;
  	if(num==4) 
	{
   		ans+=getsum(0,0,1e18,(st+sum-1)/sum,ed/sum);return;
   	}
   	solve(Max,sum,num+1),k[num]++;
	solve(Max,sum*f[num],num),k[num]--;
}
signed main() 
{
   cin>>st>>ed;
   memset(dp,-1,sizeof dp);
   solve(ed,1,0);
   cout<<ans;
   return 0;
}
