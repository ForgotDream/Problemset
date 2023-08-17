#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int a=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {a=(a<<1)+(a<<3)+ch-'0';ch=getchar();}
	return a*f;
}
int n,a[500500];
signed main(){
	
	freopen("feather.in","r",stdin);
	freopen("feather.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	a[0]=a[n];a[n+1]=a[1];
	int ans=0;
	for(int i=0;i<=n;i++){
		ans=max(ans,a[i]+a[i+1]);
	}
	cout<<ans;
	return 0;
}
