#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int s,n,ans;
signed main(){
	freopen("china.in","r",stdin);
	freopen("china.out","w",stdout);
	s=read();n=read();
	ans=s;
	for(int i=1,a,b,t;i<=n;i++){
		a=read();b=read();t=read();
		ans+=(b-a+1)*(t-1);
	}
	printf("%lld",ans);
	return 0;
}
