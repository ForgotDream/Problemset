#include<cmath>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int n,m,k1,k2,ans=0x7f7f7f7f,prex[100],prey[100];
bool vis[50][50];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int qval(int x1,int y1,int x2,int y2) {return k1*abs(x1-x2)+k2*abs(y1-y2);}
void dfs(int x,int y,int s,int val) 
{
	if(vis[x+1][y]&&vis[x-1][y]&&!vis[x][y+1]&&!vis[x][y-1]) return ;
	if(!vis[x+1][y]&&!vis[x-1][y]&&vis[x][y+1]&&vis[x][y-1]) return ;
    int res=0;
    if (s<=n*m/2) prex[s]=x,prey[s]=y;
    else res=qval(x,y,prex[s-n*m/2],prey[s-n*m/2]);
	if (val>=ans) return ;
    if (s==n*m) {ans=min(ans,max(val,res));return ;}
    for (int i=0,nx,ny;i<4;i++) 
	{
		nx=x+dx[i];ny=y+dy[i];
		if (nx<1||ny<1||nx>n||ny>m) continue;
        if (!vis[nx][ny])
		{
            vis[nx][ny]=true;
            dfs(nx,ny,s+1,max(val,res));
            vis[nx][ny]=false;
        }
    }
}
int main()
{
    cin>>n>>m>>k1>>k2;
	memset(vis,true,sizeof(vis));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			vis[i][j]=false;
    vis[1][1]=true;
    dfs(1,1,1,0);
    cout<<ans;
    return 0;
}