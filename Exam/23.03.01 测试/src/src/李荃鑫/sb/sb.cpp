#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,dis[500500],dis2[500500];
vector<int>vec[500500];
void dfs(int u,int from){
	for(auto v:vec[u]){
		if(v==from)continue;
		dis[v]=dis[u]+1;
		dfs(v,u);
	}
}
void dfs2(int u,int from){
	for(auto v:vec[u]){
		if(v==from)continue;
		dis2[v]=dis2[u]+1;
		dfs2(v,u);
	}
}
signed main(){
	freopen("sb.in","r",stdin);
	freopen("sb.out","w",stdout);
	n=read();
	for(int i=1,u,v;i<n;i++){
		u=read();v=read();
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs(1,0);
	int l=1,r=1;
	for(int i=1;i<=n;i++){
		if(dis[i]>dis[l])l=i;
	}
	memset(dis,0,sizeof dis);
	dfs(l,0);
	for(int i=1;i<=n;i++){
		if(dis[i]>dis[r])r=i;
	}
	dfs2(r,0);
	for(int i=1;i<=n;i++){
		cout<<max(dis[i],dis2[i])<<endl;
	}
	return 0;
}
