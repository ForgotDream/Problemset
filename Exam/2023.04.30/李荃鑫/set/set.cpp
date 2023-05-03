#include <algorithm>
#include <bits/stdc++.h>

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
int n,ans=1,l;
int vis[50050];
vector<int>g[200050];
inline int ksm(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=(res*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}
inline void dfs(int u){
    if(u>n)return;
    if(!vis[u]){
        vis[u]++;
        vis[2*u]++;
        vis[3*u]++;
        ans=(ans+1)%mod;
        dfs(u+1);
        vis[u]--;
        vis[2*u]--;
        vis[3*u]--;
    }
    dfs(u+1);
}
signed main(){
    freopen("set.in","r",stdin);
    freopen("set.out","w",stdout);
	n=read();
    l=n/2+1;
    dfs(1);
    cout<<ans<<endl;
    return 0;
	return ~~(0-0);
}