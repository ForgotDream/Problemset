#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,n) for(int i=0;i<(n);i++)
#define all(x) x.begin(),x.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define bits bitset<N>
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef long long ll;

template<class T> void read(T &x){
	int f=0; x=0; char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f|=(ch=='-');
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	if(f) x=-x;
}

const int N=100005,lim=100000;
bits a,b,c,ans;
int n,m,Q,x;

int main(){
	freopen("magician.in", "r", stdin);
	freopen("magician.out", "w", stdout);
	read(n),read(m),read(Q);
	rep(i,1,n){
		read(x);
		a[x].flip();
	}
	rep(i,1,m){
		read(x);
		b[x].flip();
	}
	rep(d,1,lim){
		if(!b[d]) continue;
		int k=1;
		while(2*k*d<=lim) k<<=1;
		c=a;
		for(;k;k>>=1){
			bits t=c>>(k*d);
			c^=t,c^=t<<(k*d);
		}
		ans^=c;
	} 
	while(Q--){
		read(x);
		puts(ans[x]?"1":"0");
	}
	return 0;
}
