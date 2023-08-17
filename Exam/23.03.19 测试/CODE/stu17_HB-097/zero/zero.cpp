#include<bits/stdc++.h>

using namespace std;

#define int long long

const int ze=1e8;

inline int  read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n;
int a[6][500];
bool ans[2*ze];
inline void dfs(int step,int sum){
	if(step==3){
		ans[sum+ze]=1;
		return ;
	}
	for(int i=1;i<=n;i++){
		dfs(step+1,sum+a[step][i]);
	}
}
inline void dfs2(int step,int sum){
	if(sum>ze*2)return;
	if(step==6){
		if(ans[ze-sum]){
			printf("YES");
			exit(0);
		}
		return ;
	}
	for(int i=1;i<=n;i++){
		dfs2(step+1,sum+a[step][i]);
	}
}
signed main(){
	freopen("zero.in","r",stdin);
	freopen("zero.out","w",stdout);
	n=read();
	for(int i=1;i<=5;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
		}
	}
	dfs(1,0);
	dfs2(3,0);
	printf("NO\n");
	return 0;
}
