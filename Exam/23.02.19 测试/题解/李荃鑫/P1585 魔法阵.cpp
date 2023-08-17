#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m,k1,k2,mod,ans=0x3f3f3f3f,vis[500][500],px[2550],py[2550];
int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
inline int calc(int x1,int y1,int x2,int y2){
    return k1*abs(x1-x2)+k2*abs(y1-y2);
}
inline void init() {
    memset(vis,0x3f,sizeof(vis));
    for(int i=1;i<=n;i++) {
        for(int j= 1;j<=m;j++) {
            vis[i][j]=0;
        }
    }
    vis[1][1] = 1;
}
inline void dfs(int x,int y,int step,int sum){
	if (vis[x+1][y] && vis[x-1][y] && !vis[x][y+1] && !vis[x][y-1]) return ;
    if (!vis[x+1][y] && !vis[x-1][y] && vis[x][y+1] && vis[x][y-1]) return ;

	int res=0;
    if(step<=mod){
    	px[step]=x;
    	py[step]=y;	
    }
    else res=calc(x,y,px[step-mod],py[step-mod]);
	if(sum>=ans) return ;
    if(step==n*m) {
        ans=min(ans,max(sum,res));
        return;
    }
	for(int i=0;i<=3;i++){
		int tx=x+dx[i],ty=y+dy[i];
		if(tx<=0||ty<=0||tx>n||ty>m)continue;
		if(vis[tx][ty])continue;
		vis[tx][ty]=1;
		dfs(tx,ty,step+1,max(sum,res));
		vis[tx][ty]=0;
	}
}
signed main(){
	n=read();m=read();k1=read();k2=read();
	mod=n*m/2;
	init();
	dfs(1,1,1,0);
	cout<<ans;
    return 0;
}