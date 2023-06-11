//Code by __dest__ruct__or__(uid=592238)
#include <iostream>
#include <string>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define mset multiset
#define ll long long
#define ld long double
#define ull unsigned ll
#define pii pair<int,int>
#define pll pair<ll,ll>
#define spe putchar(' ')
#define edl putchar('\n')
#define tpcTi template<class T>inline
#define ret return
const ll INF=9223372036854775807;
namespace mySTL{
	tpcTi T _max(T a,T b){ret a>b?a:b;}
	tpcTi T _min(T a,T b){ret a<b?a:b;}
	tpcTi T _abs(T a){ret a<0?-a:a;}
	inline int read(){char c=getchar();int f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans=(ans*10+c-'0'),c=getchar();
	ret ans*f;}
	inline ll readll(){char c=getchar();ll f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans=(ans*10+c-'0'),c=getchar();
	ret ans*f;}
	tpcTi void _swap(T &a,T &b){a^=b,b^=a,a^=b;}
	inline void write(int x){if(x<0){putchar('-');x=-x;}
	if(x>=10){write(x/10);}putchar(x%10+'0');}
	inline void write(ll x){if(x<0){putchar('-');x=-x;}
	if(x>=10){write(x/10);}putchar(x%10+'0');}
	inline ll pw(ll a,ll b,ll p=INF){if(b==0)ret 1;
	if(b==1)ret a%p;
	ll mid=pw(a,b/2,p)%p;
	if(b&1)ret mid*mid%p*a%p;else{ret mid*mid%p;}}
	tpcTi T gcd(T a,T b){ret b?gcd<T>(b,a%b):a;}
	tpcTi T lcm(T a,T b){ret a/gcd<T>(a,b)*b;}
	inline void write(string s){int len=s.length();
	for(int i=0;i<len;i++) putchar(s[i]);}
}
using namespace mySTL;
int n,m,opt,x,y;
ll k,a[110000],p,tree[110000*4],mtag[110000*4],atag[110000*4];
inline int lc(int x){
	ret x<<1;
}
inline int rc(int x){
	ret x<<1|1;
}
inline void build(int l,int r,int k){
	mtag[k]=1;
	if(l==r){
		tree[k]=a[l];
		ret;
	}
	int m=l+r>>1;
	build(l,m,lc(k));
	build(m+1,r,rc(k));
	tree[k]=(tree[lc(k)]+tree[rc(k)])%p;
}
inline void pushdown(int l,int r,int x){
	int m=l+r>>1;
	mtag[lc(x)]=(mtag[x]*mtag[lc(x)])%p;
	mtag[rc(x)]=(mtag[x]*mtag[rc(x)])%p;
    atag[lc(x)]=(atag[lc(x)]*mtag[x])%p;
    atag[rc(x)]=(atag[rc(x)]*mtag[x])%p;
    tree[lc(x)]=(tree[lc(x)]*mtag[x])%p;
    tree[rc(x)]=(tree[rc(x)]*mtag[x])%p;
    // 先统一处理乘法
    atag[lc(x)]=(atag[lc(x)]+atag[x])%p;
    atag[rc(x)]=(atag[rc(x)]+atag[x])%p;
    tree[lc(x)]=(tree[lc(x)]+atag[x]*(m-l+1))%p;
    tree[rc(x)]=(tree[rc(x)]+atag[x]*(r-m))%p;
    // 再统一处理加法
	mtag[x]=1;
	atag[x]=0;
}
inline void mul(int x,int y,ll z,int l,int r,int k){
	if(l>r||l>y||r<x){
		ret;
	}
	if(l>=x&&r<=y){
		mtag[k]=(mtag[k]*z)%p;
		atag[k]=(atag[k]*z)%p;
		tree[k]=(tree[k]*z)%p;
		ret;
	}
	pushdown(l,r,k);
	int m=l+r>>1;
	mul(x,y,z,l,m,lc(k));
	mul(x,y,z,m+1,r,rc(k));
	tree[k]=(tree[lc(k)]+tree[rc(k)])%p;
}
inline void add(int x,int y,ll z,int l,int r,int k){
	if(l>r||l>y||r<x){
		ret;
	}
	if(l>=x&&r<=y){
		atag[k]=(atag[k]+z)%p;
		tree[k]=(tree[k]+z*(r-l+1)%p)%p;
		ret;
	}
	pushdown(l,r,k);
	int m=l+r>>1;
	add(x,y,z,l,m,lc(k));
	add(x,y,z,m+1,r,rc(k));
	tree[k]=(tree[lc(k)]+tree[rc(k)])%p;
}
inline ll sum(int x,int y,int l,int r,int k){
	if(l>r||l>y||r<x){
		ret 0;
	}
	if(l>=x&&r<=y){
		ret tree[k];
	}
	pushdown(l,r,k);
	int m=l+r>>1;
	ret (sum(x,y,l,m,lc(k))+sum(x,y,m+1,r,rc(k)))%p;
}
int main(void){
	n=read();
	m=read();
	p=readll();
	for(int i=1;i<=n;i++){
		a[i]=readll();
		a[i]%=p;
	}
	build(1,n,1);
	while(m--){
		opt=read();
		x=read();
		y=read();
		if(opt==1){
			k=readll();
			mul(x,y,k,1,n,1);
		}else if(opt==2){
			k=readll();
			add(x,y,k,1,n,1);
		}else{
			write(sum(x,y,1,n,1)%p);
			edl;
		}
	}
	ret 0;
}
