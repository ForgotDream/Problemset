#include <bits/stdc++.h>
#include <ctime>

using namespace std;

//#define int long long
#define pii pair<int,int>

const int mod=1000000001;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m;
int ans=0;
int dis[500][500];
int vis[500];
int s[5005],len;
vector<int>path;
inline void dfs(int u,int num){
    if(u==n+1&&num>ans){
        ans=num;
        path.clear();
        for(int i=1;i<=len;i++){
            path.push_back(s[i]);
        }
        if((double)clock()/CLOCKS_PER_SEC>0.9)
        return;
    }
    if(u>n)return;
    if(!vis[u]){
        for(int i=1;i<=n;i++){
            if(dis[u][i]!=0x3f3f3f3f)vis[i]++;
        }
        s[++len]=u;
        dfs(u+1,num+1);
        s[len]=0;
        len--;
        for(int i=1;i<=n;i++){
            if(dis[u][i]!=0x3f3f3f3f)vis[i]--;
        }
    }
    dfs(u+1,num);
}
signed main(){
    freopen("travel.in","r",stdin);
    freopen("travel.out","w",stdout);
	n=read();m=read();
    memset(dis,0x3f,sizeof dis);
    for(int i=1,u,v;i<=m;i++){
       u=read();v=read();
       dis[u][v]=1;
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }
    dfs(1,0);
    cout<<ans<<endl;
    for(auto v:path)cout<<v<<" ";
	return ~~(0-0);
}