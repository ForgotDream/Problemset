#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,n) for(int i=0;i<(n);i++)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define SZ(x) ((int)x.size())
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef long long ll;
typedef double ld;

template<class T> void read(T &x){
	int f=0; x=0; char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f|=(ch=='-');
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	if(f) x=-x;
}

ll K,L,R,ans;

bool chk(ll x){
	ll sum=0,y=x;
	for(;y;y/=10) sum+=(y%10)*(y%10);
	return x/K==sum;
}

int main(){
	freopen("equation.in", "r", stdin);
	freopen("equation.out", "w", stdout);
	read(K),read(L),read(R);
	for(ll x=K;x/K<=2000&&x<=R;x+=K){
		if(L<=x&&chk(x)) ans++;
	}
	cout<<ans<<endl;
	return 0;
}
