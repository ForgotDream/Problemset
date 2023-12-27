#include<cstdio>
#include<vector>
const int M=2e5+5;
int n,m,dfc,d[M],f[M],dfn[M],siz[M],son[M],top[M];
int BIT[M];int opt[M],x[M],y[M],ans[M];
std::vector<int>G[M],id[M];
void DFS1(int u){
	dfn[u]=++dfc;d[u]=d[f[u]]+1;siz[u]=1;
	for(int&v:G[u]){
		DFS1(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void DFS2(int u,int tp){
	top[u]=tp;if(!son[u])return;DFS2(son[u],tp);
	for(int&v:G[u])if(v!=son[u])DFS2(v,v);
}
inline int LCA(int u,int v){
	while(top[u]^top[v]){
		if(d[top[u]]>d[top[v]])u=f[top[u]];
		else v=f[top[v]];
	}
	return d[u]>d[v]?v:u;
}
inline int dis(const int&u,const int&v){
	return d[u]+d[v]-(d[LCA(u,v)]<<1)+1;
}
inline void Add(int x,const int&val){
	for(;x<=n;x+=1<<__builtin_ctz(x))BIT[x]+=val;
}
inline int Query(int x){
	int ans=0;
	for(;x>=1;x-=1<<__builtin_ctz(x))ans+=BIT[x];
	return ans;
}
inline int Q(const int&x,const int&y){
	int lca=LCA(x,y);
	return Query(dfn[x])+Query(dfn[y])-Query(dfn[lca])-Query(dfn[f[lca]]);
}
signed main(){
	register int i,k;
	scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%d",f+i),G[f[i]].push_back(i);
	for(i=1;f[i];i=f[i]);
	DFS1(i);DFS2(i,i);
	scanf("%d",&m);
	for(i=1;i<=m;++i){
		scanf("%d",opt+i);
		if(opt[i]==1){
			scanf("%d%d%d",x+i,y+i,&k);
			if(k<i)id[i-k-1].push_back(i);
		}
		if(opt[i]==2){
			scanf("%d",x+i);
		}
	}
	for(i=1;i<=m;++i){
		if(opt[i]==2){
			Add(dfn[x[i]],1);Add(dfn[x[i]]+siz[x[i]],-1);
		}
		for(int&v:id[i])ans[v]=Q(x[v],y[v]);
		if(opt[i]==1){
			printf("%d %d\n",dis(x[i],y[i]),ans[i]);
		}
	}
}
