#include<bits/stdc++.h>

using namespace std;

#define int long long
#define inf 0x3f3f3f3f

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,k,maxl,maxr,vis[5005],minl;
struct node{
	int l,r,c,s;
}a[500500];
void Main1();
void Main2();
void dfs(int step,int ans,int s,int l,int r){
	if(step==k+1){
		minl=min(minl,ans);
		return ;
	}
	for(int i=1;i<=n;i++){
		if(l>a[i].l&&r>a[i].r&&!vis[i]){
			vis[i]=1;
			ans+=(s-a[i].s)*a[i].c;
			vis[i]=0;
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		vis[i]=1;
		dfs(step+1,ans,s,max(a[i].l,l),max(a[i].r,r));
		vis[i]=0;
	}
}
signed main(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		a[i].l=read();
		a[i].r=read();
		a[i].c=read();
		a[i].s=a[i].l*a[i].r;
		maxl=max(maxl,a[i].l);
		maxr=max(maxr,a[i].r);
	}
	if(k==1)Main1();
	if(k==n){cout<<0<<endl;return 0;}
	dfs(1,0,0,0,0);
	cout<<minl;
	return 0;
}
void Main1(){
	int s=maxl*maxr;
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=(s-a[i].s)*a[i].c;
	}
	cout<<ans<<endl;
	exit(0);
}
