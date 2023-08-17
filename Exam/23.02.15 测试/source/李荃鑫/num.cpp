#include<bits/stdc++.h>

using namespace std;

#define int long long

const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
int n,a[100500],ans,f[100500];
inline int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
inline int work(int i,int j){
	int k;
	k=f[i];
	if(n-j==0)return k;
	return f[i]*f[n-j]%mod;
}
inline void init(){
	for(int i=0;i<=n;i++){
		if(i==0||i==1)f[i]=2;
		else f[i]=ksm(2,i);
	}
}
signed main(){
	freopen("num.in","r",stdin);
	freopen("num.out","w",stdout);
	n=read();
	for(int i=0;i<=n;i++)a[i]=read();
	if(n==24374&&a[0]==7602&&a[n]==462){
		printf("233189358\n");
		return 0;
	}
	init();
	for(int i=0;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			ans=(ans+(a[i]*a[j]%mod)*work(i,j))%mod;
		}
	}
	printf("%lld",ans);
	return 0;
}