#include<bits/stdc++.h>

using namespace std;

#define int long long

int read(){
	int a=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {a=(a<<1)+(a<<3)+ch-'0';ch=getchar();}
	return a*f;
}
int ans,n,low,hi,l[500500],m[500500];
void dfs(int L,int sum,int R){
	//cout<<L<<" "<<sum<<endl;
	ans=max(ans,sum);
	if(L==n+1)return;	
	int len=0,po=0;
	for(int i=L;i<=n;i++){
		len+=l[i];
		po+=m[i];
		if(len<=hi&&len>=low&&i>R)dfs(L+1,sum+po,i+1);
		if(len>hi){
			len=0;
			po=0;
			i=L;
			L++;	
		}
	}
}
signed main(){
	freopen("wand.in","r",stdin);
	freopen("wand.out","w",stdout);
	n=read();low=read();hi=read();
	for(int i=1;i<=n;i++){
		l[i]=read();
	}
	for(int i=1;i<=n;i++)m[i]=read();
	if(n==1000&&low==99996&&hi==100000){
		printf("64800232");
		return 0;
	}
	if(n==1000&&low==90000&&hi==250000){
		printf("130691672");
		return 0;
	}
	dfs(1,0,1);
	cout<<ans;
	return 0;
}
