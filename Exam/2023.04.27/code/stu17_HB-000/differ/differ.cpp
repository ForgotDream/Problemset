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
int m,n;
vector<pii>g[10500];
queue<int>q;
int dis[10500];
bool vis[10500];
inline void spfa1(){
	memset(dis,128,sizeof dis);
	q.push(0);
	vis[0]=1;
	dis[0]=0;
	while(q.size()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(auto i:g[u]){
			int v=i.first,w=i.second;
			if(dis[v]<dis[u]+w){
				dis[v]=dis[u]+w;
				if(!vis[v]){
					//cnt[v]++;
					vis[v]=1;
					q.push(v);
					//if(cnt[v]>n)return;
				}
			}
		}
	}
}
signed main(){
	freopen("differ.in","r",stdin);
	freopen("differ.out","w",stdout);
	m=read();n=read();
	int op,xi,xj,w;
	for(int i=1;i<=n;i++){
		op=read();
		if(op==0){
			xi=read();xj=read();w=read();
			g[xj].push_back({xi,w});
		}
		if(op==1){
			xi=read();xj=read();w=read();
			g[xi].push_back({xj,-w});
		}
		if(op==2){
			xi=read();xj=read();w=read();
			g[xj].push_back({xi,w});
			g[xi].push_back({xj,-w});
		}
	}
	for(int i=1;i<=m;i++)g[0].push_back({i,0});
	spfa1();
	int q=read();
	while(q--){
		xi=read();xj=read();
		if(dis[xi]==dis[0]||dis[xj]==dis[0])printf("Infinity\n");
		else printf("%d\n",dis[xi]-dis[xj]);
	}
	return 0;
}
