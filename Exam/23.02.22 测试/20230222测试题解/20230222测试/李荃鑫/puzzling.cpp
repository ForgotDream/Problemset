#include<bits/stdc++.h>

using namespace std;

//#define int long long

inline int read(){
	int a=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {a=(a<<1)+(a<<3)+ch-'0';ch=getchar();}
	return a*f;
}
int n,vis[5005],sl;
struct node{
	int m[20][20];
	int chang,kuan;
}a[3200];
int g[505][50];
bool check(){
	for(int i=1;i<=sl;i++){
		for(int j=1;j<=sl;j++){
			if(g[i][j]==0)return 0;
		}
	}
	return 1;
}
void print(){
	for(int i=1;i<=sl;i++){
		for(int j=1;j<=sl;j++){
			printf("%d",g[i][j]);
		}
		printf("\n");
	}
}
bool kefang(int x,int y,int id){
	for(int i=x;i<x+a[id].chang;i++){
		for(int j=y;j<y+a[id].kuan;j++){
			if(a[id].m[i-x+1][j-y+1]==0)continue;
			if(i>sl||j>sl)return 0;
			if(g[i][j]!=0)return 0;
		}
	}
	return 1;
}
void filld(int x,int y,int id){
	for(int i=x;i<x+a[id].chang;i++){
		for(int j=y;j<y+a[id].kuan;j++){
			if(a[id].m[i-x+1][j-y+1]==0)continue;
			if(i>sl||j>sl)continue;
			g[i][j]=id;
		}
	}
}
void cleard(int x,int y,int id){
	for(int i=x;i<x+a[id].chang;i++){
		for(int j=y;j<y+a[id].kuan;j++){
			if(a[id].m[i-x+1][j-y+1]==0)continue;
			if(i>sl||j>sl)continue;
			g[i][j]=0;
		}
	}
}
void dfs(int step){
	if(step==n){
		print();
		exit(0);
	}
	if(step>n){
		printf("-1");
		return;
	}
	for(int i=1;i<=sl;i++){
		for(int j=1;j<=sl;j++){
			if(g[i][j]==0){
				for(int k=1;k<=n;k++){
					//cout<<n<<endl;
					//if(i==1&&j==3)cout<<k<<"  hfdjskfh"<<endl;
					if(vis[k])continue;
					if(kefang(i,j,k)){
						vis[k]=1;
						filld(i,j,k);
						//print();
						dfs(step+1);
						cleard(i,j,k);
						vis[k]=0;
						//cout<<"hfdjskhfdjks"<<endl;
					}
				}
			}
		}
	}
}
signed main(){
	freopen("puzzling.in","r",stdin);
	freopen("puzzling.out","w",stdout);
	n=read();
	for(int i=1,l,r;i<=n;i++){
		l=read();r=read();
		for(int j=1;j<=l;j++){
			for(int k=1;k<=r;k++){
				scanf("%1d",&a[i].m[j][k]);
				if(a[i].m[j][k])sl++;
			}
		}
		a[i].chang=l;a[i].kuan=r;
	}
	//cout<<sl<<endl;
	sl=(int)sqrt(sl);
	//cout<<sl<<endl;
	dfs(0);
	printf("-1");
	return 0;
}
