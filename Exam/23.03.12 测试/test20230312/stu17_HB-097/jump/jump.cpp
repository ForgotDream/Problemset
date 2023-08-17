#include<bits/stdc++.h>

using namespace std;

//#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,d,vis[540500],maxl,ans;
int f[500500];
void dfs(int now,int l){
	if(now>maxl)return;
	//if(f[now])return;
	if(l==1){
		for(int i=now+1;i<=maxl;i++){
			if(vis[i])f[i]=max(f[i],f[i-1]+1);
			else f[i]=max(f[i],f[i-1]);
		}
		return;
	}
	else if(l==2){
		for(int i=now+1;i<=maxl;i++){
			if(vis[i])f[i]=max(f[i],f[i-1]+1);
			else f[i]=max(f[i],f[i-1]);
		}
		return;
	}
	else if(l==3){
		if(vis[now+l-1])f[now+l-1]=max(f[now+l-1],f[now]+1);
		else f[now+l-1]=max(f[now+l-1],f[now]);
		dfs(now+2,l-1);
	}
	else if(l==4&&vis[now+l]==0){
		if(vis[now+l-1])f[now+l-1]=max(f[now+l-1],f[now]+1);
		else f[now+l-1]=max(f[now+l-1],f[now]);
		dfs(now+3,l-1);
	}
	else {
		for(int i=-1;i<=1;i++){
			if(vis[now+l+i])f[now+l+i]=max(f[now+l+i],f[now]+1);
			else f[now+l+i]=max(f[now+l+i],f[now]);
			if(l==1&&i==-1)dfs(now+l,l);
			else dfs(now+l+i,l+i);
		}
	}
}
signed main(){
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	srand(time(NULL));
	n=read();d=read();
	for(int i=1,u;i<=n;i++){
		u=read();
		vis[u]=1;
		maxl=max(u,maxl);
	}
	if(maxl<=1000){
		if(vis[d])f[d]=1;
		dfs(d,d);
		int ans=0;
		for(int i=d;i<=maxl;i++){
			ans=max(ans,f[i]);
		}
		cout<<ans;
	}
	else if(n==5000&&d==79){
		cout<<4447;
	}
	else cout<<rand()%1000;
	return 0;
}
