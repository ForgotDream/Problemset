#include<bits/stdc++.h>
#define MAXN 18
#define p 1000000007
using namespace std;
int n,m,ma[20][20];
int f[MAXN][MAXN][270000];
int g[MAXN][MAXN][270000];
int ans[20][20];
void modify(int &a,int b)//卡常，用%的话会变慢
{
	a+=b;
	if(a>p)a-=p;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&ma[i][j]),ma[i][j]^=1;
	int max_state=(1<<m+1)-1;
	f[0][m][0]=1;
	for(int i=1;i<=n;i++)//正着dp
	{
		for(int j=0;j<=max_state;j++)modify(f[i][0][j<<1],f[i-1][m][j]);//转移这一行的初始状态
		for(int j=1;j<=m;j++)
			for(int k=0;k<=max_state;k++)
			{
				int val=f[i][j-1][k];
				if(!val)continue;
				int pl1=(k>>j-1)&1;//右插头
				int pl2=(k>>j)&1;//下插头
				if(!ma[i][j]){if(!pl1&&!pl2)modify(f[i][j][k],val);}//第一种情况
				else if(!pl1&&!pl2)//第二种情况
				{
					modify(f[i][j][k],val);
					if(ma[i+1][j])modify(f[i][j][k^(1<<j-1)],val);
					if(ma[i][j+1])modify(f[i][j][k^(1<<j)],val);
				}
				else if(!pl1&&pl2)//第三种情况
					modify(f[i][j][k^(1<<j)],val);
				else if(pl1&&!pl2)//第三种情况
					modify(f[i][j][k^(1<<j-1)],val);
			}
	}
	g[n+1][1][0]=1;
	for(int i=n;i>0;i--)//反着dp与正着dp同理，反过来就好了
	{
		for(int j=0;j<=max_state;j++)modify(g[i][m+1][j>>1],g[i+1][1][j]);
		for(int j=m;j>0;j--)
			for(int k=0;k<=max_state;k++)
			{
				int val=g[i][j+1][k];
				if(!val)continue;
				int pl1=(k>>j-1)&1;
				int pl2=(k>>j)&1;
				if(!ma[i][j]){if(!pl1&&!pl2)modify(g[i][j][k],val);}
				else if(!pl1&&!pl2)
				{
					modify(g[i][j][k],val);
					if(ma[i-1][j])modify(g[i][j][k^(1<<j)],val);
					if(ma[i][j-1])modify(g[i][j][k^(1<<j-1)],val);
				}
				else if(!pl1&&pl2)
					modify(g[i][j][k^(1<<j)],val);
				else if(pl1&&!pl2)
					modify(g[i][j][k^(1<<j-1)],val);
			}
	}
  auto print = [&](int x) {
    for (int i = 0; i < m + 1; i++) { std::cerr << !!(x & (1 << i)); }
    std::cerr << "\n";
  };
	for(int i=1;i<=n;i++)//合并答案
		for(int j=1;j<=m;j++)
		{
			if(!ma[i][j])continue;
			int now=max_state^(1<<j-1)^(1<<j);//合法状态
			for(int k=now;k;k=(k-1)&now)//取合法状态的所有子集
				modify(ans[i][j],1ll*f[i][j-1][k]*g[i][j+1][k]%p), cerr << g[i][j+1][k] << "\t", print(k);
			cerr << g[i][j+1][0] << "\t", print(0);
      modify(ans[i][j],1ll*f[i][j-1][0]*g[i][j+1][0]%p);//0也是合法状态
      cerr << "\n";
		}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%d ",ans[i][j]);//输出即可
		puts("");
	}
	return 0;
}
