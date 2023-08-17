#include<bits/stdc++.h>

using namespace std;

#define int long long
#define inf 0x3f3f3f3f

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,a[5005],m,b[5005],summ,sumn;
bool vis[2500],vis2[5005];
int ton[100500],ton2[100500];
struct node{
	int d,s;
};
queue<node>q;
queue<node>qq;
inline void dfs(int now,int step,int s[],int w[],int l);
inline void bfs1();
inline void bfs2();
inline void Main1();
inline void Main2();
inline int Min(int x,int y){return x<y?x:y;}
signed main(){
	freopen("packs.in","r",stdin);
	freopen("packs.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sumn+=a[i];
	}
	m=read();
	for(int i=1;i<=m;i++){
		b[i]=read();
		summ+=b[i]	;
	}
	if(n<=10&&m<=10)Main1();
	else Main2();
	return 0;
}
inline void Main2(){
	for(int i=1;i<=n;i++){
		ton[a[i]]=1;
	}
	q.push({0,0});
	memset(ton,0x3f,sizeof ton);
	bfs1();
	//cout<<ton[8]<<endl;
	for(int i=1;i<=m;i++){
		ton2[b[i]]=1;
	}
	qq.push({0,0});
	memset(ton2,0x3f,sizeof ton2);
	bfs2();
	int ans=inf;
	for(int i=1;i<=100000;i++){
		if(ton[i]<=inf&&ton2[i]<=inf){
			//cout<<i<<' '<<ton[i]<<' '<<ton2[i]<<endl;
			ans=min(ans,ton[i]+ton2[i]);
			//cout<<"hfdsjkfjds"<<endl;
		}
	}
	if(ans!=inf)cout<<ans;
	else cout<<"impossible";
}
inline void Main1(){
	memset(ton,0x3f,sizeof ton);
	memset(ton2,0x3f,sizeof ton2);
	dfs(0,0,a,ton,n);
	memset(vis,0,sizeof vis);
	dfs(0,0,b,ton2,m);
	int ans=inf;
	for(int i=1;i<=1000;i++){
		if(ton[i]<=inf&&ton2[i]<=inf){
			ans=Min(ans,ton[i]+ton2[i]);
		}
	}
	if(ans!=inf)cout<<ans;
	else cout<<"impossible";
	exit(0);
}
inline void dfs(int now,int step,int s[],int w[],int l){
	w[now]=Min(w[now],step);
	for(int i=1;i<=l;i++){
		if(vis[i])continue;
		vis[i]=1;
		dfs(now+s[i],step+1,s,w,l);
		vis[i]=0;
	}
}
void bfs1(){
	while(q.size()){
		node u=q.front();q.pop();
		if(u.s>=n)break;
		//cout<<u.d<<' '<<u.s<<endl;
		for(int i=1,td,ts;i<=n;i++){
			//if(vis[i])continue;
			//vis[i]=1;
			td=u.d+a[i];ts=u.s+1;
			if(td>=sumn)continue;
			//cout<<td<<" "<<ts<<endl;
			if(ton[td]<inf)continue;
			ton[td]=ts;
			q.push({td,ts});
		}
	}
}
void bfs2(){
	while(qq.size()){
		node u=qq.front();qq.pop();
		if(u.s>=m)break;
		for(int i=1,td,ts;i<=m;i++){
			td=u.d+b[i];ts=u.s+1;
			if(td>=summ)continue;
			if(ton2[td]<inf)continue;
			ton2[td]=ts;
			qq.push({td,ts});
		}
	}
}
