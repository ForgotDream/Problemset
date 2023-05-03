# include <iostream>
# include <cstdio>
# include <cstring>
# include <queue>
using namespace std;
int read(){
	int s=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){s=(s<<1)+(s<<3)+ch-'0';ch=getchar();}
	return s*f;
}
const int N=400;
const int M=1e5+7;
const int inf=1e9;
int n,m;
int t,x,y,z,Q;
struct edge{
	int to,nt,w;
}e[M];int hd[N],cnt;
void add_e(int x,int y,int z){
	e[++cnt]=(edge){y,hd[x],z};hd[x]=cnt;
}
int dis[N][N],book[N];
void build(){
	n=read();m=read();
	for(int i=1;i<=m;++i){
		t=read();x=read();y=read();z=read();
		if(t==0) add_e(y,x,z);
		if(t==1) add_e(x,y,-z);
		if(t==2) add_e(y,x,z),add_e(x,y,-z);
	}
}
void spfa(int s){
	deque <int> q;memset(book,0,sizeof(book));
	for(int i=1;i<=300;++i) dis[s][i]=inf;
	dis[s][s]=0;q.push_back(s);book[s]=1;
	while(q.size()>0){
		int u=q.front();q.pop_front();book[u]=0;int v;
		for(int i=hd[u];i;i=e[i].nt){
			v=e[i].to;
			if(dis[s][v]>dis[s][u]+e[i].w){
				dis[s][v]=dis[s][u]+e[i].w;
				if(!book[v]){
					q.push_back(v);book[v]=1; 
				}
			}
		}
	} 
}
void work(){
	for(int i=1;i<=n;++i) spfa(i);
	Q=read();
	for(int i=1;i<=Q;++i){
		x=read();y=read();
		if(dis[y][x]==inf) cout<<"Infinity"<<endl;
		if(dis[y][x]<inf) cout<<dis[y][x]<<endl;
	}
}
int main(){
	freopen("differ.in","r",stdin);
	freopen("differ.out","w",stdout);
	build();
	work();
	return 0;
}
