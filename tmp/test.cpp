#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#define int long long
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1) 
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=3e5+10;
const int mod=1e9+9;
const int M=383008016;
inline int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=(res*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return res;
}
inline int inv(int x){
	if(x<0)x+=mod;
	return ksm(x,mod-2);
}
const int Inv=inv(M);
inline int calc(int a,int p,int n){
	return ((((ksm(p,n)-1+mod)%mod)*inv(p-1)%mod)*a)%mod;
}
int n,q,a[N],b[N];
struct Tree{
	int P,sum[N<<2],tag[N<<2];
	inline void pushup(int p){
		sum[p]=(sum[ls]+sum[rs])%mod;
	}
	inline void f(int p,int l,int r,int k){
		sum[p]+=calc(k,P,r-l+1);
		tag[p]+=k;
		sum[p]%=mod;
		tag[p]%=mod;
	}
	inline void pushdown(int p,int l,int r){
		if(!tag[p])return;
		int len=mid-l+1;
		f(ls,l,mid,tag[p]);
		f(rs,mid+1,r,(tag[p]*ksm(P,len))%mod);
		tag[p]=0;
	}
	void update(int L,int R,int p,int l,int r,int k){
		if(L==l&&r==R){
			sum[p]+=calc(k,P,r-l+1);
			tag[p]+=k;
			sum[p]%=mod;
			tag[p]%=mod;
			return;
		}
		pushdown(p,l,r);
		int len=mid-L+1;
		if (R <= mid) {
		    update(L, R, ls, l, mid, k);
		} else if (L > mid) {
		    update(L, R, rs, mid + 1, r, k);
		} else {
		    update(L, mid, ls, l, mid, k);
		    update(mid + 1, R, rs, mid + 1, r, (k * ksm(P, len)) % mod);
		}
		pushup(p);
	}
	int query(int L,int R,int p,int l,int r){
		if(L<=l&&r<=R)
			return sum[p];
		pushdown(p,l,r);
		int res=0;
		if(L<=mid)(res+=query(L,R,ls,l,mid)) %= mod;
		if(R>mid) (res+=query(L,R,rs,mid+1,r)) %= mod;
		return res%mod;
	}
}T1,T2;
signed main()
{
	T1.P=((1+M)*inv(2))%mod;
	T2.P=(((1-M+mod)%mod)*inv(2))%mod;
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=(b[i-1]+a[i])%mod;
	}
	while(q--){
		int opt=read(),l=read(),r=read();
		if(opt==1){
			T1.update(l,r,1,1,n,T1.P);
			T2.update(l,r,1,1,n,T2.P);
		}
		if(opt==2){
			int s1=T1.query(l,r,1,1,n),s2=T2.query(l,r,1,1,n),s3=((b[r]-b[l-1]) % mod+mod)%mod;
            std::cerr << s1 << " " << s2 << "\n";
			int res=(s1-s2+mod)%mod;
			res=(res*Inv)%mod;
			res=(res+s3)%mod;
			printf("%lld",res);
			putchar('\n');
		}
	}
	return 0;
}
