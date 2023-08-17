#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int a=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {a=(a<<1)+(a<<3)+ch-'0';ch=getchar();}
	return a*f;
}
int n,m,t,a[500500],b[50050];
vector<int>vec[500500];
signed main(){
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	n=read();m=read();t=read();
	for(int i=1;i<=n;i++)a[i]=read();
	int l=0;
	for(int i=1;i<=n;i++){
		if(a[i]==m){
			l=i;
			break;	
		}
	}
	for(int i=1;i<=l;i++){
		a[n+i]=a[i];
	}
	for(int i=1;i<=n;i++){
		if(t>=i)b[a[i]]=a[l+t-i];
		else b[a[i]]=a[l+t+n-i];
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",b[i]);
	}
	return 0;
}
