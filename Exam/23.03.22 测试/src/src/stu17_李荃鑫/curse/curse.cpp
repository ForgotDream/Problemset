#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n;
string a[1200],ans;
signed main(){
	freopen("curse.in","r",stdin);
	freopen("curse.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int len=a[1].size();
	for(int i=0;i<len;i++){
		int res=0;
		for(int j=1;j<=n;j++){
			if(a[j][i]=='1')res++;
		}
		if(res*2<=n)ans+="0";
		else ans+="1";
	}
	cout<<ans;
	return 0;
}
