#include<bits/stdc++.h>

using namespace std;

//#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m,k;
double dis[1200][1200];
string s;
signed main(){
	freopen("compare.in","r",stdin);
	freopen("compare.out","w",stdout);
	n=read();m=read();k=read();
	memset(dis,77,sizeof dis);
	double w;
	for(int i=0;i<=n;i++)dis[i][i]=0;
	for(int i=1,u,v;i<=m;i++){
		u=read();v=read();scanf("%lf",&w);
		dis[u][v]=dis[v][u]=min(w,dis[u][v]);
	}
	getline(cin,s);
	int tag=0;
	double maxl=1e14;
	while(k--){
		getline(cin,s);
		//cout<<s<<endl;
		if(s[0]=='I')continue;
		int last=s[0]-48,flag=0,flag2=0;
		double ans=0;
		for(int i=1;i<s.size();i++){
			int x=0;
			while(s[i]>='0'&&s[i]<='9'){x=x*10+s[i]-48;i++;}
			if(x!=0){
				//cout<<x<<endl;
				if(x>n){
					flag=1;
					break;
				}
				if(x==n)flag2=1;
				if(dis[last][x]==dis[1][0]){
					flag=1;
					break;	
				}
				ans+=dis[last][x];
				last=x;
			}
		}
		//cout<<ans<<endl;
		if(!flag&&flag2){
			tag=1;
			maxl=min(maxl,ans);	
		}
	}
	if(tag==1)printf("%.4lf",maxl);
	else printf("Wrong");
	return 0;
}
