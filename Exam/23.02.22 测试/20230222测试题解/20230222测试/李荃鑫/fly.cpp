#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int a=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {a=(a<<1)+(a<<3)+ch-'0';ch=getchar();}
	return a*f;
}
struct node{
	int x,y;
}a[5005];
double eps=1.4142135;
int K,n,m,f[1500500];
inline cmp(node a,node b){
	if(a.x==b.x)return a.y>b.y;//tmdzhelikenlewolianggexiaoshi
	return a.x<b.x;
}
signed main(){
	freopen("fly.in","r",stdin)                            ;
	freopen("fly.out","w",stdout);
	n=read();m=read();
	K=read();
	for(int i=1;i<=K;i++)f[i]=1;
	for(int i=1;i<=K;i++){
		a[i].x=read();
		a[i].y=read();
	}
	sort(a+1,a+1+K,cmp);
	for(int i=1;i<=K;i++){
		for(int j=1;j<i;j++){
			if(a[j].x<a[i].x&&a[j].y<a[i].y)
			f[i]=max(f[i],f[j]+1);
		}
	}
	int len=0;
	for(int i=1;i<=K;i++){
		len=max(len,f[i]);
	}
	//cout<<len<<endl;
	double s=(n+m)*100-len*200+len*eps*100;
	int t=s*10;
	if(t%10>=5)t+=10;
	cout<<t/10;
	return 0;
}