#include<bits/stdc++.h>
using namespace std;
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
#define rep( i, s, t ) for( int i = s; i <= t; ++ i )
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
const int N =  150000 + 5; 
const int inf = 1234567890;
struct E {
	int from, to, a, b;
} e[N];
struct LCT {
	int son[2], fa, mx, id;
	bool mark;
} t[N];
int n, m, Idnum, ans, w[N], st[N];
bool cmp( E x, E y ) {
	return ( x.a == y.a ) ? x.b < y.b : x.a < y.a ;
}
bool isroot( int x ) {
	return ( ls(t[x].fa) != x ) && ( rs(t[x].fa) != x );
}
void pushup( int x ) {
	t[x].mx = w[x], t[x].id = x;
	if( ls(x) && t[ls(x)].mx > t[x].mx ) t[x].mx = t[ls(x)].mx, t[x].id = t[ls(x)].id;
	if( rs(x) && t[rs(x)].mx > t[x].mx ) t[x].mx = t[rs(x)].mx, t[x].id = t[rs(x)].id;
}
void rotate( int x ) {
	int f = t[x].fa, ff = t[f].fa, qwq = ( rs(f) == x );
	t[x].fa = ff;
	if( !isroot(f) ) t[ff].son[rs(ff) == f] = x;
	t[f].son[qwq] = t[x].son[qwq ^ 1], t[t[x].son[qwq ^ 1]].fa = f;
	t[x].son[qwq ^ 1] = f, t[f].fa = x;
	pushup(f), pushup(x);
}
void pushmark( int x ) {
	if( t[x].mark ) {
		t[x].mark = 0, t[ls(x)].mark ^= 1, t[rs(x)].mark ^= 1,
		swap( ls(x), rs(x) );
	}
} 
void Splay( int x ) {
	int top = 0, now = x; st[++top] = now;
	while( !isroot(now) ) st[++top] = ( now = t[now].fa );
	while( top ) pushmark( st[top--] );
	while( !isroot(x) ) {
		int f = t[x].fa, ff = t[f].fa;
		if( !isroot(f) ) ( ( rs(ff) == f ) ^ ( rs(f) == x ) ) ? rotate(x) : rotate(f) ;
		rotate(x);
	}
}
void access( int x ) {
	for( int y = 0; x; y = x, x = t[y].fa )
		Splay(x), t[x].son[1] = y, pushup(x);
}
void makeroot( int x ) {
	access(x), Splay(x), t[x].mark ^= 1, pushmark(x);
}
int findroot( int x ) {
	access(x), Splay(x), pushmark(x);
	while( ls(x) ) pushmark( x = ls(x) );
	return x;
}
void split( int x, int y ) {
	makeroot(x), access(y), Splay(y);
}
void link( int x, int y ) {
	makeroot(x);
	if( findroot(y) != x ) t[x].fa = y;
}
bool check( int x, int y ) {
	makeroot(x);
	return findroot(y) != x;
}
signed main()
{
	n = read(), m = read(), ans = inf;
	rep( i, 1, m ) e[i].from = read(), e[i].to = read(), e[i].a = read(), e[i].b = read();
	sort( e + 1, e + m + 1, cmp );
	rep( i, 1, m ) {
		w[i + n] = e[i].b;
		if( e[i].from == e[i].to ) continue;
		if( check( e[i].from, e[i].to ) ) link( e[i].from, i + n ), link( i + n, e[i].to );
		else {
			split( e[i].from, e[i].to );
			int now = t[e[i].to].id, maxb = t[e[i].to].mx;
      // std::cerr << now << " " << maxb << "\n";
			if( maxb <= e[i].b ) continue;
			Splay( now ), t[ls(now)].fa = t[rs(now)].fa = 0;
			link( e[i].from, i + n ), link( i + n, e[i].to );
		} 
		if( !check( 1, n ) ) {
			split( 1, n ); ans = min( ans, t[n].mx + e[i].a );
		}
	}
	if( ans == inf ) puts("-1");
	else printf("%d\n", ans);
	return 0;
}