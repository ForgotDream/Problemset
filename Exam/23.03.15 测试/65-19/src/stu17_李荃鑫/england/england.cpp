#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,a[200000],maxl;
signed main(){
	freopen("england.in","r",stdin);
	freopen("england.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	int t;
	for(int i=1;i<=n;i++){
		int l=i,r=i;
		while(l>=1&&a[l]>=a[i])l--;
		while(r<=n&&a[r]>=a[i])r++;
		//cout<<l<<' '<<r<<endl;
		t=(r-l-1)*a[i];
		maxl=t>maxl?t:maxl;
	}
	printf("%lld",maxl);
	return 0;
}
