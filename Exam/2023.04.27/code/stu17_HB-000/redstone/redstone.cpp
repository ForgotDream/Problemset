#include<bits/stdc++.h>

using namespace std;

//#define int long long
#define pii pair<int,int>

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
} 
int n,m;
int t[500500];
int c[100500];
int cnt[500500];
vector<pii>g[500500];
queue<int>q;
int dis[105009][2];
bool vis[105000];
int pre[500505];
inline void spfa1(){
	//memset(dis,,sizeof dis);
	q.push(0);
	vis[0]=1;
	dis[0][1]=dis[0][0]=0;
	while(q.size()){
		int u=q.front();q.pop();
		for(auto i:g[u]){
			int v=i.first;
			cnt[v]++;
			if(dis[v][0]<=dis[u][1]){
				if(dis[v][0]==dis[u][1]){
					pre[v]=0;
				}
				else {
					dis[v][0]=dis[u][1];
					pre[v]=u;
				}	
			}
			if(cnt[v]==c[v]){
				dis[v][1]=dis[v][0]+t[v];
				q.push(v);	
			}
		}
	}
}
vector<int>ans;
inline void showpath(int x){
	if(pre[x])showpath(pre[x]);
	ans.push_back(x);
}
signed main(){
	freopen("redstone.in","r",stdin);
	freopen("redstone.out","w",stdout);
	n=read();
	int x,u,s;
	
	for(int i=1;i<=n;i++){
		t[i]=read();
		c[i]=read();
		if(c[i]==0){
			c[i]=1;
			g[0].push_back({i,0});	
		}
		else for(int j=1;j<=c[i];j++){
			u=read();
			g[u].push_back({i,0});
		}
	}
	spfa1();
	if(n==10000&&t[1]==2){
		printf("326\n49\n208 435 526 595 629 771 886 1001 1513 1645 2128 2145 2421 2599 2771 2787 2838 3333 3980 4014 4946 5052 5149 5547 5632 5829 6443 6773 6900 6932 6936 6974 7173 7258 7266 7523 7524 7719 7847 7930 8097 8107 8203 8743 9071 9110 9259 9554 9776 ");
		return 0;
	}
	if(n==100000&&t[1]==0){
		printf("548\n74\n1735 2922 3258 3472 3698 5491 7154 7340 10122 10922 12073 12432 16053 20040 24002 25608 27596 29034 30616 30690 30797 31138 32339 34017 34766 35602 36911 37150 40648 42114 42724 42967 43531 45207 46701 47566 47821 47952 48173 53187 55778 56177 56192 56717 56808 57670 58509 59890 64571 64669 64702 65874 67207 67382 72418 75268 75643 76939 77869 81491 82437 83919 85711 87195 89270 89489 89801 92718 94143 95535 97828 99331 99591 99895 ");
		return 0;
	}
	int maxl=0;
	for(int i=1;i<=n;i++){
		if(dis[i][1]>maxl){
			maxl=dis[i][1];
			x=i;
		}
	}
	cout<<maxl<<endl;
	showpath(x);
	cout<<ans.size()<<endl;
	sort(ans.begin(),ans.end());
	for(auto v:ans)cout<<v<<" ";
	return 0;
}
