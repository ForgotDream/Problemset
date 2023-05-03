#include<cstdio>
#include<deque>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<memory>
#include<queue>
#include<cmath>
#include<shared_mutex>
#include<utility>
#include<ctime>
using namespace std;
typedef unsigned long long ull;
typedef long double ldouble ;
ull A,B;
int num[25],len;
ull ten[25];
ull dfs(int pos,ldouble nowNum,ldouble nowSum,bool isSmall)
{
	if (pos==0) return A<=nowNum*nowSum&&nowNum*nowSum<=B;
	if (nowNum*ten[pos]*nowSum>B) return 0;
	int MM=isSmall?9:num[pos];
	ull res=0;
	for (int i=1;i<=MM;i++)
		res+=dfs(pos-1,nowNum*10+i,nowSum*i,isSmall||i<num[pos]);
	return res;
}
inline ull solve(int date)
{
	len=0;
	while (date)
	{
		len++;
		num[len]=date%10;
		date/=10;
	}
	ull res=0;
	for (int i=1;i<=len;i++)
		for (int j=1;j<=(i==len?num[i]:9);j++)
			res+=dfs(i-1,j,j,j<num[i]||i!=len);
	return res;
}
inline ull check(ull Date)
{
	ldouble res=Date;
	while (Date)
	{
		res*=Date%10;
		Date/=10;
	}
	return A<=res&&res<=B;
}
int main()
{
	freopen("sillyz.in","r",stdin);
    freopen("sillyz.in","w",stdout);
	ten[0]=1;
	for (int i=1;i<=18;i++)
		ten[i]=ten[i-1]*10;
	cin>>A>>B;
	if (B<=1000000)
	{
		int ans=0;
		for(ull i=1;i<=B;i++)
			if(check(i))
				ans++;
		cout<<ans;
		return 0;
	}
	cout<<solve(B);
	return 0;
}