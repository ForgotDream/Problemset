#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,an,bn,cn,dn,m,ans;
int a[8005],b[8005],c[8005],d[8005];
int ab[25005000],cd[25000500],cishu[25000500];
signed main(){
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
	n=read();an=read();bn=read();cn=read();dn=read();
	for(int i=1;i<=an;i++)a[i]=read();
	for(int i=1;i<=bn;i++)b[i]=read();
	for(int i=1;i<=cn;i++)c[i]=read();
	for(int i=1;i<=dn;i++)d[i]=read();
	int len=0,t;
	for(int i=1;i<=an;i++){
		for(int j=1;j<=bn;j++){
			ab[++len]=a[i]+b[j];
		}
	}
	//sort(ab+1,ab+1+len);
	m=len;len=0;
	for(int i=1;i<=cn;i++){
		for(int j=1;j<=dn;j++){
			cd[++len]=c[i]+d[j];
		}
	}
	sort(cd+1,cd+1+len);
	for(int i=1;i<=len;i++)cishu[i]=cishu[i-1]+1;
	int low=0,upp=0;
	int key;
	for(int i=1;i<=m;i++){
		upp=(upper_bound(cd+1,cd+1+len,n-ab[i])-cd);
		//if(low==upp)continue;
		ans+=cishu[upp-1];
	}
	cout<<ans;
	return 0;
}


