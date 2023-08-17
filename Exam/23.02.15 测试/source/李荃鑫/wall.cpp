#include<bits/stdc++.h>

using namespace std;

//#define int long long
#define eps 1e-4;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
int n,h,vis[5005],out[5005],book[5005];
int dis[1005][1005],ans=0x3f3f3f3f;
struct node{
	int x,y;
}a[5005];
inline int dist(int i,int j){
	int k=sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y));
	if(k-1000<=0)return 1;
	return 0;
}
struct d{
	int x,step;
};
void bfs(int s){
	queue<d>q;
	q.push({s,1});
	memset(vis,0,sizeof vis);
	vis[s]=1;
	while(q.size()){
		d u=q.front();q.pop();
		if(out[u.x]){
			ans=min(ans,u.step);
			break;
		}
		for(int i=1;i<=n;i++){
			if(dis[u.x][i]&&!vis[i]){
				vis[i]=1;
				int step=u.step+1;
				q.push({i,step});
			}
		}
	}
}
signed main(){
	freopen("wall.in","r",stdin);
	freopen("wall.out","w",stdout);
	h=read();n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read();
		a[i].y=read();
		if(a[i].y>=h-1000)book[i]=1;
		if(a[i].y<=1000)out[i]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			dis[i][j]=dis[j][i]=dist(i,j);
		}
	}
	for(int i=1;i<=n;i++){
		if(book[i]==1){
			bfs(i);
		}
	}
	printf("%d",ans);
	return 0;
}