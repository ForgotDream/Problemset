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
int n,m,k,T;
int Map[510][510];
inline void debug()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cout<<Map[i][j]<<' ';
		}
		cout<<'\n';
	}
	cout<<'\n';
}
bool book[510];
int temp[1000],head=1,tail;
int main()
{
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	cin>>n>>m>>T;
	for(int i=1;i<=n;i++)
	{
		cin>>Map[m][i];
		Map[Map[m][i]][i]=m;
		tail++;
		temp[tail]=Map[m][i];
	}
	book[m]=true;
	//debug();
	for(int tt=1,pos;tt<=n-1;tt++)
	{
		tail++;
		temp[tail]=temp[head];
		head++;
		bool flag=false;
		for(int i=1;i<=n;i++)
		{
			if (book[i]) continue;
			if (flag) break;
			flag=true;pos=i;
			for (int j=1;j<=n;j++)
				if (Map[i][j])
					if (Map[i][j]!=temp[head+j-1])
					{
						flag=false;	
						break;
					}
		}
		for (int i=1;i<=n;i++)
		{
			Map[pos][i]=temp[head+i-1];
		}
	}
	for (int i=1;i<=n;i++)
	{
		if (Map[i][T]==-1) cout<<i<<' ';
		else cout<<Map[i][T]<<' ';
	}
	return 0;
}
