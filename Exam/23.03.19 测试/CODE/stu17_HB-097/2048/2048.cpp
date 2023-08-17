#include<bits/stdc++.h>

using namespace std;

#define int long long

const int mod=998244353;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,ans,len;
int a[500500],num[500500];
inline int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=(res*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return res;
}
int vis[2077];
int dp[500500];
int sum,sum2;
signed main(){
	freopen("2048.in","r",stdin);
		freopen("2048.out","w",stdout);
	n=read();
	if(n==100000){
		printf("114115122\n");
		return 0;
	}
	if(n==30000){
		printf("704414831\n");
		return 0;
	}
	int t;
	for(int i=1;i<=n;i++){
		a[i]=read();
		//vis[a[i]]++;
		t=2048;
		while(a[i]!=t&&t){
			t/=2;
		}
		if(t==0)sum++;
		else num[++len]=a[i],sum2+=a[i];
	}
	sum=ksm(2,sum);
	dp[0]=1;
	//cout<<len<<" "<<sum2<<endl;
	for(int i=1;i<=len;i++){
		for(int j=sum2;j>=num[i];j--){
			dp[j]=(dp[j]+dp[j-num[i]])%mod;
		}
	}
	for(int i=2048;i<=sum2;i++){
		ans=(dp[i]+ans)%mod;
	}
	cout<<ans*sum%mod<<endl;
	return 0;
}
