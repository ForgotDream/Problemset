#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int  read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int sum;
inline void gcd(int a,int b){
	if(b==0)return;
	sum+=a/b;
	//cout<<sum<<endl;
	gcd(b,a%b);
}
signed main(){
	freopen("sword.in","r",stdin);
	freopen("sword.out","w",stdout);
	int T=read();
	int a,b;
	while(T--){
		sum=0;
		a=read();b=read();
		if(a<b)swap(a,b);
		gcd(a,b);
		printf("%lld\n",sum-1);
	}
	return 0;
}
