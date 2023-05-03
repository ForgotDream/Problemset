#include<bits/stdc++.h>

using namespace std;

//#define int long long
#define eps 1e-7

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct node{
	double x,y;
}a[10];
double ans;
double lx1,rx1,lx2,rx2;
double k1,k2,b1,b2;
inline double dist(int x1,int y1,int x2,int y2){
	return sqrtl((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
inline double check(int i){
	if(i==1||i==2){
		double k3=-1/k2,b3=a[i].y-k3*a[i].x;
		double x1=((b2-b3)/(k3-k2));
		double y1=k2*x1+b2;
		double dis=dist(a[i].x,a[i].y,x1,y1);
		//cout<<dis<<" "<<x1<<endl;
		//cout<<k2<<endl;
		if(k2==0&&a[1].x>lx2&&a[1].x<rx2)return dis;
		if(x1>lx2&&x1<rx2)return dis;
		else return 1e12;
	}
	if(i==3||i==4){
		double k3=-1/k1,b3=a[i].y-k3*a[i].x;
		double x1=((b1-b3)/(k3-k1));
		double y1=k1*x1+b1;
		double dis=dist(a[i].x,a[i].y,x1,y1);
		//cout<<dis<<endl;
		//if(x1==nan)return dis
		if(k1==0&&a[3].x>lx1&&a[3].x<rx1)return dis;
		if(x1>lx1&&x1<rx1)return dis;
		else return 1e12;
	}
	return 1e12;
}
signed main(){
	//ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	freopen("segment.in","r",stdin);
	freopen("segment.out","w",stdout);
	for(int i=1;i<=4;i++){
		cin>>a[i].x>>a[i].y;
	}
	k1=(a[1].y-a[2].y)/(a[1].x-a[2].x);
	k2=(a[3].y-a[4].y)/(a[3].x-a[4].x);
	b1=a[1].y-a[1].x*k1;
	b2=a[3].y-a[3].x*k2;
	lx1=min(a[1].x,a[2].x);
	rx1=max(a[1].x,a[2].x);
	lx2=min(a[3].x,a[4].x);
	rx2=max(a[3].x,a[4].x);
	
	//cout<<k1<<" "<<b1<<endl;
	//cout<<k2<<" "<<b2<<endl;
	if(fabs(k1-k2)<eps&&fabs(b1-b2)<eps){
		cout<<"0.0000"<<endl;
		return 0;
	}
	double x0=(b2-b1)/(k1-k2);
	double y0=(k1*x0)+b1;
	if(x0>lx1&&x0>lx2&&x0<rx1&&x0<rx2){
		cout<<"0.0000"<<endl;
		return 0;
	}
	ans=min(min(dist(a[1].x,a[1].y,a[3].x,a[3].y),dist(a[2].x,a[2].y,a[4].x,a[4].y)),min(dist(a[1].x,a[1].y,a[4].x,a[4].y),dist(a[2].x,a[2].y,a[3].x,a[3].y)));
	for(int i=1;i<=4;i++)ans=min(ans,check(i));
	printf("%.4lf",ans);
	return 0;
}
