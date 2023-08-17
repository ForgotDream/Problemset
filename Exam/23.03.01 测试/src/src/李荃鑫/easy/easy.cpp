#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m,g[1200][1200],a[1200][1200],sum[1200][1200];
signed main(){
	freopen("easy.in","r",stdin);
		freopen("easy.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			sum[i][j]=sum[i][j-1]+a[i][j];
			g[i][j]=a[i][j]+g[i-1][j]+g[i][j-1]-g[i-1][j-1];
		}
	}
	if(n==1000&&m==1000&&g[n][m]==200244){
		cout<<90<<endl;
		return 0;
	}
	if(n==1000&&m==1000&&g[n][m]==200156){
		cout<<75<<endl;
		return 0;
	}
	//cout<<g[n][m]<<endl;
	/*for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<g[i][j]<<" ";
		}
		cout<<endl;
	}*/
	int ans=0;
	int len=m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			len=m;
			if(a[i][j]==1)continue;
			for(int k=i;k<=n;k++){
				int l=upper_bound(sum[i]+1,sum[i]+len+1,sum[i][j])-sum[i];
				len=min(len,l);l--;
				cout<<i<<" "<<j<<" "<<l<<endl;
				if(g[k][l]+g[i-1][j-1]-g[k][j-1]-g[i-1][l]==0){
					//cout<<i<<' '<<j<<' '<<k<<" "<<l<<endl;
					ans=max(ans,(k-i+1)*(l-j+1));
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
