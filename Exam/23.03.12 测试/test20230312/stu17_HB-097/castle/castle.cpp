#include<bits/stdc++.h>

using namespace std;

#define int long long

const int mod=1e9+7;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,k,r;
inline int ksm(int a,int b){
	int res=1;
	a=a%mod;
	while(b){
		if(b&1)res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
signed main(){
	freopen("castle.in","r",stdin);
	freopen("castle.out","w",stdout);
	n=read();k=read();
	int t=ksm(n-k,n-k);
	int l=ksm(k,k-1);
	cout<<t*l%mod;
	return 0;
}
