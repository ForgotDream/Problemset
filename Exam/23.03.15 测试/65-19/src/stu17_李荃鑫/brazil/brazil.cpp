#include<bits/stdc++.h>

using namespace std;

//#define int long long
#define inf 1e7
#define eps 1e-5

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,m;
struct node{
	int x,y;
}zz[5005],lm[5005];
double dis[500][500];
bool vis[500];
inline double check(int i,int j){
	 double k=(double)(zz[i].y-zz[j].y)/(zz[i].x-zz[j].x);
	 double b=(double)zz[i].y-zz[i].x*k;
	 
	 for(int l=1;l<=m;l++){
	 	if(lm[l].x>max(zz[i].x,zz[j].x)||lm[i].x<min(zz[i].x,zz[j].x))continue;
	 	if(lm[l].x*k+b-lm[l].y<=eps){
	 		//if(i==1&&j==3)cout<<l<<endl;
	 		return inf;
	 	}
	 }
	 return sqrt((zz[i].x-zz[j].x)*(zz[i].x-zz[j].x)+(zz[i].y-zz[j].y)*(zz[i].y-zz[j].y));
}
signed main(){
	freopen("brazil.in","r",stdin);
	freopen("brazil.out","w",stdout);
	zz[0].x=read();zz[0].y=read();n=read();m=read();
	for(int i=1;i<=n;i++){
		zz[i].x=read();
		zz[i].y=read();
	}
	for(int i=1;i<=m;i++){
		lm[i].x=read();
		lm[i].y=read();
	}
	for(int i=0;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(i==0){
				dis[i][j]=inf;
				dis[j][i]=2*sqrt((zz[i].x-zz[j].x)*(zz[i].x-zz[j].x)+(zz[i].y-zz[j].y)*(zz[i].y-zz[j].y));
			}
			else{
				dis[i][j]=dis[j][i]=check(i,j);
			}
		}	
	}
	/*for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%.4lf ",dis[i][j]);
		}
		printf("\n");
	}*/
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	double ans=inf;
	for(int i=1;i<=n;i++){
		ans=min(ans,dis[i][0]+dis[1][i]);
	}
	int t=ans*10;
	if(t%10>=5)printf("%d",t/10+1);
	else printf("%d",t/10);
	return 0;
}
