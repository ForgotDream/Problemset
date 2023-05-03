#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<cmath>
#include<map>
#include<queue>
#define mod 1000000001
#define inf 2000000000
#define ll long long 
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
ll tot=1;
int bin[20];
int n;
int a[20][20],b[20],f[20][2048];
bool mark[100005],jud[2048][2048];
int cal(int x)
{
	memset(b,0,sizeof(b));
	a[1][1]=x;
	for(int i=2;i<=18;i++)
		if(a[i-1][1]*2<=n)
			a[i][1]=a[i-1][1]*2;
		else a[i][1]=n+1;
	for(int i=1;i<=18;i++)
		for(int j=2;j<=11;j++)
			if(a[i][j-1]*3<=n)
				a[i][j]=a[i][j-1]*3;
			else a[i][j]=n+1;
	for(int i=1;i<=18;i++)
		for(int j=1;j<=11;j++)
			if(a[i][j]<=n)
			{
				b[i]+=bin[j-1];
				mark[a[i][j]]=1;
			}
	for(int i=0;i<=18;i++)
		for(int x=0;x<=b[i];x++)
			f[i][x]=0;
	f[0][0]=1;
	for(int i=0;i<18;i++)
		for(int x=0;x<=b[i];x++)
		{
			if(f[i][x])
				for(int y=0;y<=b[i+1];y++)
					if(jud[x][y])
						f[i+1][y]=(f[i][x]+f[i+1][y])%mod;
					}
	return f[18][0];
}
int main()
{
	freopen("set.in","r",stdin);
	freopen("set.out","w",stdout);
	for(int i=0;i<=2047;i++)
		for(int j=0;j<=2047;j++)
			if((i&j)==0&&(j&(j>>1))==0)jud[i][j]=1;
	bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
	n=read();
	for(int i=1;i<=n;i++)
		if(!mark[i])tot=(tot*cal(i))%mod;
	printf("%d",tot);
	return 0;
}

