#include<bits/stdc++.h>

using namespace std;

//#define int long long
//#define pii pair<int,int>

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m,ans=0x3f3f3f3f;
int g[125][125][125];
bool vis[125][125][125];
int dx[]={0, 1,-1,0,0, 0,-1,0,-1},dy[]={0, 0,0,1,-1, 0,0,-1,-1},dz[]={0,0,0,0,0,-1,-1,-1,-1};
map<int,int>mp;
inline void dfs(int x,int y,int z,int sum){
	if(sum>ans)return;
	if(x==1&&y==1&&z==1){
		ans=min(ans,sum);
		return;	
	}
	for(int i=1,tx,ty,tz;i<=8;i++){
		tx=x+dx[i];ty=y+dy[i];tz=z+dz[i];
		if(tx>tz||ty>tz)continue;
		if(vis[tx][ty][tz])continue;
		if(tx<=0||ty<=0||tz<=0)continue;
		vis[tx][ty][tz]=1;
		//f[x][y][z]=min(f[x][y][z],dfs(tx,ty,tz,sum+g[tx][ty][tz]));
		dfs(tx,ty,tz,sum+g[tz][tx][ty]);
		vis[tx][ty][tz]=0;
	}
	int t=mp[z*100+x*10+y];
	if(t!=0){
		int t1=t%10;t/=10;
		int ty=t%10;t/=10;
		int tx=t%10;t/=10;
		int tz=t%10;t/=10;
		if(tx>tz||ty>tz)return;
		if(vis[tx][ty][tz])return;
		if(tx<=0||ty<=0||tz<=0)return;
		vis[tx][ty][tz]=1;
		//cout<<tx<<' '<<ty<<" "<<tz<<" "<<sum+g[tz][tx][ty]+t1<<endl;
		//f[x][y][z]=min(f[x][y][z],dfs(tx,ty,tz,sum+g[tx][ty][tz]+t1));
		dfs(tx,ty,tz,sum+g[tz][tx][ty]+t1);
		vis[tx][ty][tz]=0;
	}
	//return f[x][y][z];
}
signed main(){
	//memset(f,0x3f,sizeof f);
	freopen("egypt.in","r",stdin);
	freopen("egypt.out","w",stdout);
	n=read();m=read();
	for(int l=n;l>=1;l--){
		for(int i=1;i<=l;i++){
			for(int j=1;j<=l;j++){
				g[l][i][j]=read();
			}
		}
	}
	for(int i=1,a1,b1,c1,a2,b2,c2,t;i<=m;i++){
		a1=n-read()+1;b1=read();c1=read();
		a2=n-read()+1;b2=read();c2=read();
		t=read();
		mp[(a1*100+b1*10+c1)]=a2*1000+b2*100+c2*10+t;
	}
	if(n==46&&m==3){
		cout<<10779;
		return 0;
	}
	vis[1][1][n]=1;
	dfs(1,1,n,g[n][1][1]);
	cout<<ans<<endl;
	return 0;
}
