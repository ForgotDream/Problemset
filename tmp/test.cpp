#include<bits/stdc++.h>
#define int long long
using namespace std;
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
	x=r*w;
}
const int N=1e5+7,mod=1e9+7;
int f[N],s[N],cnt,p[N];
map<int,int>mp;
void init()
{
	p[0]=1;
	for(int i=1;i<=1e5;i++)p[i]=p[i-1]*i%mod;
}
int Pow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int C(int n,int m)
{
	if(m==0)return 1;
	if(n<m)return 0;
	return p[n]*Pow(p[m],mod-2)%mod*Pow(p[n-m],mod-2)%mod;
}
bool check(int x)
{
	while(x)
	{
		if(x%10!=4&&x%10!=7)return false;
		x/=10;
	}
	return true;
}
main()
{
	init();
	int n,k,t=0;
	read(n);read(k);
	for(int i=1,x;i<=n;i++)
	{
		read(x);
		if(check(x))
		{
			if(!mp[x])mp[x]=++cnt;
			s[mp[x]]++;
		}
		else t++;
	}
	f[0]=1;
	for(int i=1;i<=cnt;i++)
	for(int j=cnt;j>=1;j--)
		f[j]=(f[j]+f[j-1]*s[i]%mod)%mod;
	int ans=0;
	for(int i=0;i<=k;i++)
		ans=(ans+f[i]*C(t,k-i)%mod)%mod;
	cout<<ans;
	return 0;
}
