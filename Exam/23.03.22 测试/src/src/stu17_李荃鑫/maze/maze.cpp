#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m,dis[500500],dis2[500500];
vector<pair<int,int> >vec[500500];
bool vis[500500];
queue<int>q;
void spfa(){
	memset(dis,0x3f,sizeof dis);
	memset(dis2,0x3f,sizeof dis2);
	q.push(1);
	vis[1]=1;dis[1]=0;
	while(q.size()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(auto i:vec[u]){
			int v=i.first,w=i.second;
			if(dis[v]<dis[u]+w){
				dis2[v]=min(dis2[v],dis[u]+w);
			}
			if(dis[v]>dis[u]+w){
				dis2[v]=min(dis2[v],dis[v]);
				dis[v]=dis[u]+w;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
}
signed main(){
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
	n=read();m=read();
	for(int i=1,u,v,w;i<=m;i++){
		u=read();v=read();w=read();
		vec[u].push_back({v,w});
		vec[v].push_back({u,w});
	}
	spfa();
	cout<<dis2[n]<<endl;
	return 0;
}
