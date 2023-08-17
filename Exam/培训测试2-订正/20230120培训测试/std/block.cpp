#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define maxn 300005
#define maxm 3000005
#define ll long long 
using namespace std;

int n,m,i,j,k,L[maxn],R[maxn],h[maxn],cnt;
ll t[maxm],tag[maxm]; int tl[maxm],tr[maxm];
struct arr{int x,i,t;} a[maxn*2]; 
int cmp(arr a,arr b){return a.x<b.x;}

void downtag(int x,int l,int r){
	t[x]=tag[x];
	if (l<r) tag[x<<1]=tag[x<<1^1]=tag[x];
	tag[x]=0;
}
ll find(int x,int l,int r,int L,int R){
	if (tag[x]) downtag(x,l,r);
	if (L<=l&&r<=R) return t[x];
	if (l>R||r<L) return 0;
	int mid=(l+r)>>1;
	return max(find(x<<1,l,mid,L,R),find(x<<1^1,mid+1,r,L,R));
}
void cover(int x,int l,int r,int L,int R,ll v){
	if (tag[x]) downtag(x,l,r);
	if (l>R||r<L) return;
	if (L<=l&&r<=R) {tag[x]=v,downtag(x,l,r);return;}
	int mid=(l+r)>>1;
	cover(x<<1,l,mid,L,R,v),cover(x<<1^1,mid+1,r,L,R,v);
	t[x]=max(t[x<<1],t[x<<1^1]);
}
void read(int &x){
	x=0; char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar());
	for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
}

int main(){
	read(n);
	for(i=1;i<=n;i++) read(L[i]),read(R[i]),read(h[i]);
	for(i=1;i<=n;i++) a[++cnt]=(arr){L[i],i,1},a[++cnt]=(arr){R[i],i,2};
	sort(a+1,a+1+cnt,cmp);
	for(i=1;i<=cnt;i++){
		if (i==1||a[i].x!=a[i-1].x) m++;
		if (a[i].t==1) L[a[i].i]=m; else R[a[i].i]=m;
	}
	for(i=1;i<=n;i++){
		ll v=find(1,1,m,L[i],R[i]);
		cover(1,1,m,L[i],R[i],v+h[i]);
	}
	printf("%lld\n",t[1]);
}
