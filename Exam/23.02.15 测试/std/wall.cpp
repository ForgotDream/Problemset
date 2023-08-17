#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int N=1e6+50;
const int W=0x7f7f7f7f;
struct edge{
	int nxt;
	int to;
	int w;
}e[N<<1];	int head[N],cnt;
int dis[N];
int h,n;
struct node{
	int x,y;
}v[N];
struct VD{
	int to;
	int dis;
	bool operator <(const VD &b)const{
		return dis>b.dis;
	}
};
double calc(int x1,int y1,int x2,int y2){
	return sqrt(1.0*(x1-x2)*(x1-x2)+1.0*(y1-y2)*(y1-y2));
}
void add(int f,int t,int w){
	e[++cnt]=(edge){head[f],t,w};head[f]=cnt;
}
void dijkstra(int s){
	priority_queue<VD> q;
	for(int i=1; i<=n; i++) dis[i]=W;
	dis[s]=1;
	q.push((VD){s,1});
	while(q.size()){
		VD temp;
		temp=q.top();q.pop();
		int p=temp.to;
		if(temp.dis>dis[p]) continue;
		for(int i=head[p]; i; i=e[i].nxt){
			int t=e[i].to;
			if(dis[t]>dis[p]+e[i].w){
				dis[t]=dis[p]+e[i].w;
				temp.to=t,temp.dis=dis[t];
				q.push(temp);
			}
		}
	}
	return;
}
int main(){
	freopen("wall.in","r",stdin);
	freopen("wall.out","w",stdout);
	scanf("%d%d",&h,&n);
	for(int i=1; i<=n; i++){
		scanf("%d%d",&v[i].x,&v[i].y);
	}
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			if(calc(v[i].x,v[i].y,v[j].x,v[j].y)<=1000) add(i,j,1),add(j,i,1);
		}
	}
	int ans=W;
	for(int i=1; i<=n; i++){
		if(v[i].y<=1000){
			dijkstra(i);
			for(int j=1; j<=n; j++){
				if(h-v[j].y<=1000) ans=min(ans,dis[j]);
			}
		}
	}
	printf("%d",ans);
	return 0;
}
