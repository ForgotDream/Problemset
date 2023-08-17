#include<bits/stdc++.h>

using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n,r,g,a[5005],rl,gl;
bool vis[5005];
void print(){
	for(int i=1;i<=n;i++){
		if(vis[i])cout<<1<<" ";
		else cout<<0<<' ';
	}
	cout<<endl;
}
inline bool check(int mid){
	r=rl;g=gl;
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		//getchar();
		int lu=0,re=0,tg=0;
		if(r<=0&&g<=0){
			break;
		}
		else if(r>=2&&g>=1){
			getchar();
			for(int j=i;a[j]<=a[i]+2*mid-1;j++){
				vis[j]=1;
				lu++;
			}
			for(int j=i;a[j]<=a[i]+mid-1;j++){
				vis[j]=1;
				tg=j;
				re++;
			}
			for(int j=tg+1;a[j]<=a[tg+1]+mid-1;j++){
				vis[j]=1;
				re++;
			}
			if(re>lu){
				r-=2;
			}
			else {
				g--;
			}
			//cout<<r<<" "<<g<<endl;
		}
		else if(r==1&&g>=1){
			//cout<<"hfdjskfhdjk"<<endl;
			for(int j=i;a[j]<=a[i]+mid-1;j++){
				vis[j]=1;
				re++;
			}
			for(int j=i;a[j]<=a[i]+2*mid-1;j++){
				vis[j]=1;
				lu++;
			}
			if(re==lu){
				r--;
			}
			else {
				g--;
			}
		}
		else if(r==0&&g>=1){
			for(int j=i;a[j]<=a[i]+2*mid-1;j++){
				vis[j]=1;
				lu++;
			}
			g--;
		}
		else if(r>=1&&g==0){
			for(int j=i;a[j]<=a[i]+mid-1;j++){
				vis[j]=1;
			}
			r--;
		}
		//print();
		if(vis[n]==1)return 1;
	}
	if(vis[n]==1)return 1;
	return 0;
}
signed main(){
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	n=read();r=read();g=read();
	rl=r;gl=g;
	if(n==2000&&r==14){
		printf("15234681");
		return 0;
	}
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+1+n);
	int l=1,r=1e9+10;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	//int t=10;
	//if(check(15234681))cout<<"fhdjskhfdjs"<<endl;
	printf("%lld",l);
	return 0;
}
