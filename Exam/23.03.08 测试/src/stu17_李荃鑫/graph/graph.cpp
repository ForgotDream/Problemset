#include<bits/stdc++.h>

using namespace std;

#define int long long
#define pii pair<int,int>

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m,a[150050];double ans=0;
bool vis[500500];
vector<pii>vec[500500];
void main1();
signed main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1,u,v,w;i<=m;i++){
		u=read();v=read();w=read();
		vec[u].push_back({v,w});
		vec[v].push_back({u,w});
	}
	if(m==0){printf("0");return 0;}
	if(n==2){main1();return 0;}
	for(int i=1;i<=n;i++){
		for(auto j:vec[i]){
			int v=j.first,w=j.second;
			ans=max(ans,(double)a[i]+a[v]/w);
		}
	}
	if(ans==0)printf("0");
	else printf("%.2lf",ans);
	return 0;
}
void main1(){
	int w=vec[1][0].second;
	double dian=a[1]+a[2];
	printf("%.2lf",dian/w);
}

