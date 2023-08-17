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
//#define int unsigned long long
#define base 30000
int n,d;
int Gold[50000];
struct CASE
{
	int pos;
	int L;
	int gold;
}temp;
queue<CASE>q;
int ans;
int Nex[3]={1,-1,0};
unordered_map<unsigned long long ,int >book;
unordered_map<unsigned long long ,int >vis;
int maxid;
signed main()
{
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	scanf("%d %d",&n,&d);
	for (int i=1,pos;i<=n;i++)
	{
		scanf("%d",&pos);
		Gold[pos]=1;
		maxid=max(maxid,pos);
	}
	maxid=max(maxid,n);
	if (Gold[d]) ans=1;
	q.push(CASE{d,d,ans});
	book[d*base+d]=ans;
	vis[d*base+d]=true;
	int pos,L,Next,NextL,gold;
	while (!q.empty())
	{
		temp=q.front();q.pop();
		pos=temp.pos;
		L=temp.L;
		gold=temp.gold;
		for (int i=0;i<3;i++)
		{
			NextL=L+Nex[i];
			Next=pos+NextL;
			if (NextL>=1)
				if (Next<=maxid&&(book[Next*base+NextL]<(gold+Gold[Next])||vis[Next*base+NextL]==false)) 
				{
					book[Next*base+NextL]=(gold+Gold[Next]);
					vis[Next*base+NextL]=true;
					ans=max(ans,gold+Gold[Next]);
					q.push(CASE{Next,NextL,gold+Gold[Next]});
				}
		}
	}
	printf("%d",ans);
	return 0;
}
