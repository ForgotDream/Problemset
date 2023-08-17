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
int n,q,x,y,f[5005000];
inline int dis(int x1,int y1,int x2,int y2){
	return abs(x1-x2)+abs(y1-y2);
}
inline int calamin(int i,int xa,int ya,int xb,int yb){
	if(x<=xa&&x>=xb&&y<=ya&&y>=yb){
		return 0;
	}
	if(x<=xa&&x>=xb){
		return min(abs(y-ya),abs(y-yb));
	}
	if(y<=ya&&y>=yb){
		return min(abs(x-xa),abs(x-xb));
	}
	int q,w,e,r;
	q=dis(x,y,xa,ya);
	w=dis(x,y,xb,yb);
	e=dis(x,y,xa,yb);
	r=dis(x,y,xb,ya);
	return min(min(q,w),min(e,r));
}
inline int calamax(int i,int xa,int ya,int xb,int yb){
	int q,w,e,r;
	q=dis(x,y,xa,ya);
	w=dis(x,y,xb,yb);
	e=dis(x,y,xa,yb);
	r=dis(x,y,xb,ya);
	return max(max(q,w),max(e,r));
}
signed main(){
	freopen("bird.in","r",stdin);
	freopen("bird.out","w",stdout);
	n=read();q=read();
	x=read();y=read();
	int l,r,xa,ya,xb,yb,maxl=0;
	for(int i=1,q,w,e,r;i<=n;i++){
		q=read();w=read();e=read();r=read();
		xa=max(q,e);
		ya=max(w,r);
		xb=min(q,e);
		yb=min(w,r);
		l=calamin(i,xa,ya,xb,yb);
		r=calamax(i,xa,ya,xb,yb);
		//maxl=max(r,maxl);
		//cout<<l<<" "<<r<<endl;
		f[l]++;
		f[r+1]--;
	}
	for(int i=1;i<=2100000;i++){
		f[i]+=f[i-1];
	}
	int ask;
	while(q--){
		ask=read();
		printf("%lld\n",f[ask]);
	}
	return 0;
}

