#include<bits/stdc++.h>

using namespace std;

//#define int long long
#define pii pair<int,int>

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
} 
int n,m,s,Q;
int re[500500],gr[500500];
vector<pii>g[500500];
int dis[500500][2];
bool vis[500500];
priority_queue<pii,vector<pii>,greater<pii> >q;
inline void djs(){
	memset(dis,0x3f,sizeof dis);
	dis[s][1]=re[s];
	dis[s][0]=re[s];
	q.push({dis[s][1],s});
	while(q.size()){
		int u=q.top().second;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(auto i:g[u]){
			int v=i.first,w=i.second;
			if(dis[v][0]>dis[u][1]+w){
				dis[v][0]=dis[u][1]+w;
				if(dis[v][0]%(re[v]+gr[v])>re[v])dis[v][1]=dis[v][0];
				else dis[v][1]=dis[v][0]+re[v]-dis[v][0]%(re[v]+gr[v]);
				q.push({dis[v][1],v});
			}
		}
	}
}
signed main(){
	freopen("traffic.in","r",stdin);
	freopen("traffic.out","w",stdout);
	n=read();m=read();s=read();Q=read();
	for(int i=1;i<=n;i++){
		re[i]=read();
		gr[i]=read();
	}
	while(m--){
		int u=read(),v=read(),w=read();
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	djs();
	cout<<dis[Q][0];
	return 0;
}
