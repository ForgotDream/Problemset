#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,a[500500],h[5005];
inline bool cmp(int l,int r){
	return l>r;
}
bool check(int x){
	int len=0,sum=0,last=-1;
	while(sum!=last){
		last=sum;
		for(int i=1;i<=x;i++){
			if(h[i]==0)continue;
			if(len==n)break;
			h[i]=min(h[i]-1,a[++len]);
			//if(x==2)cout<<i<<" "<<h[i]<<" "<<a[len]<<endl;
			sum++;
		}
	}
	if(sum==n)return 1;
	else return 0;
}
signed main(){
	freopen("box.in","r",stdin);
	freopen("box.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+1+n,cmp);
	int l=1,r=n,ans;
	for(int i=1;i<=n;i++){
		memset(h,0x3f,sizeof h);
		if(check(i)){
			printf("%lld",i);
			break;
		}
	}
	return 0;
}
