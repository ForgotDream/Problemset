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
using namespace std;
#define ll long long 
int n,m,k;
struct BLOCK
{
	int type;
	int dir;
	int n,m;
	char Map[10][10];
	BLOCK()
	{
		type=dir=0;
		memset(Map,0,sizeof(Map));
	}
	void print()
	{
		for (int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cout<<Map[i][j];
			}
			cout<<'\n';
		}
		cout<<'\n';
	}
}block[10];
int len,size;
int Map[15][15];
inline bool check(int x,int y,int pos)
{
	if (x+block[pos].n-1>len) return false;
	if (y+block[pos].m-1>len) return false;
	for (int i=x;i<x+block[pos].n;i++)
		for(int j=y;j<y+block[pos].m;j++)
			if (Map[i][j]&&block[pos].Map[i-x+1][j-y+1]=='1') return false;
	return true;
}
inline void col(int x,int y,int pos)
{
	for (int i=x;i<x+block[pos].n;i++)
		for(int j=y;j<y+block[pos].m;j++)
			if (block[pos].Map[i-x+1][j-y+1]=='1') Map[i][j]=pos;
}
inline void recol(int x,int y,int pos)
{
	for (int i=x;i<x+block[pos].n;i++)
		for(int j=y;j<y+block[pos].m;j++)
			if (block[pos].Map[i-x+1][j-y+1]=='1') Map[i][j]=0;
}
bool use[10];
inline void debug()
{
	for(int i=1;i<=len;i++)
	{
		for(int j=1;j<=len;j++)
		{
			cout<<Map[i][j];
		}
		cout<<'\n';
	}
	cout<<'\n';
}
void dfs(int x,int y)
{
	//if (Map[x][y]) {dfs(x,y+1);return ;}
	if (y>len) {dfs(x+1,1);return ;}
	if (x==len+1)
	{
		for(int i=1;i<=len;i++)
			for (int j=1;j<=len;j++)
				if (!Map[i][j]) return ;
		for(int i=1;i<=len;i++)
		{
			for (int j=1;j<=len;j++)
				cout<<Map[i][j];
			cout<<endl;	
		}
		exit(0);
	}
	for (int i=1;i<=n;i++)
	{
		if (use[i]) continue;
		else if (check(x,y,i))
		{
			col(x,y,i);
			use[i]=true;
			//debug();
			dfs(x,y+1);
			use[i]=false;
			recol(x,y,i);
			//debug();
		}
	}
	dfs(x,y+1);
}
int main()
{
	freopen("puzzling.in","r",stdin);
	freopen("puzzling.out","w",stdout);
	cin>>n;
	for(int t=1,x,y;t<=n;t++)
	{
		cin>>block[t].n>>block[t].m;
		for (int i=1;i<=block[t].n;i++)
		{
			for (int j=1;j<=block[t].m;j++)
			{
				cin>>block[t].Map[i][j];
				while (block[t].Map[i][j]!='0'&&block[t].Map[i][j]!='1')
					cin>>block[t].Map[i][j];
				if (block[t].Map[i][j]=='1') size++;
			}
		}
	}
	len=sqrt(size);
	if (len*len!=size)
	{
		cout<<-1;
		return 0;
	}
	dfs(1,1);
	cout<<-1;
	return 0;
}
