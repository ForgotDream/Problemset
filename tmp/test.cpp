#include <cmath>
#include <ctime>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rint int
using namespace std;
typedef long long ll;

const int maxn = 1.5e5 + 10;
const int inf = 0x3f3f3f3f;
int n, q, A, maxsiz, tsiz, rt, cnt, head[maxn], v[maxn], Fa[maxn];
int dep[maxn], dis[maxn], siz[maxn], son[maxn], top[maxn], fa[maxn];
bool vis[maxn];
ll lastans;

struct Edge {
	int to, nxt, val;
}e[maxn << 1];

struct Node {
	int v; ll sum;
	bool operator < (const Node &B) const {
		return v < B.v;
	}
};
vector < Node > vec[2][maxn];

template <typename T> T read(T x = 0, bool f = 0, char ch = getchar()) {
	for(;!isdigit(ch);ch = getchar()) f = ch == '-';
	for(; isdigit(ch);ch = getchar()) x = (x << 3) + (x << 1) + (ch & 15);
	return f ? -x : x ;
}

void add(rint x, rint y, rint z) {
	e[++cnt] = (Edge){y, head[x], z}, head[x] = cnt;
}

void dfs1(rint x, rint prt) {
	fa[x] = prt, dep[x] = dep[prt] + 1, siz[x] = 1;
	for(rint i = head[x], y;i;i = e[i].nxt) {
		if((y = e[i].to) == prt) continue;
		dis[y] = dis[x] + e[i].val;
		dfs1(y, x);
		siz[x] += siz[y];
		if(!son[x] || siz[y] > siz[son[x]]) son[x] = y;
	}
}

void dfs2(rint x, rint tp) {
	top[x] = tp;
	if(son[x]) dfs2(son[x], tp);
	for(rint i = head[x], y;i;i = e[i].nxt) {
		if((y = e[i].to) != fa[x] && y != son[x]) dfs2(y, y);
	}
}

int Dis(rint a, rint b) {
	rint x = a, y = b;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	x = dep[x] < dep[y] ? x : y;
	return dis[a] + dis[b] - dis[x] * 2;
}

void getrt(rint x, rint prt) {
	siz[x] = 1;
	rint maxs = 0;
	for(rint i = head[x], y;i;i = e[i].nxt) {
		if(vis[y = e[i].to] || y == prt) continue;
		getrt(y, x);
		siz[x] += siz[y];
		maxs = max(maxs, siz[y]);
	}
	maxs = max(maxs, tsiz - siz[x]);
	if(maxs < maxsiz) maxsiz = maxs, rt = x;
}

void dfs(rint x, rint prt, rint sum) {
	siz[x] = 1;
	vec[0][rt].push_back((Node){v[x], sum});
	if(Fa[rt]) vec[1][rt].push_back((Node){v[x], Dis(x, Fa[rt])});
	for(rint i = head[x], y;i;i = e[i].nxt) {
		if(vis[y = e[i].to] || y == prt) continue;
		dfs(y, x, sum + e[i].val);
		siz[x] += siz[y];
	}
}

void solve(rint x) {
	vis[x] = 1, dfs(x, 0, 0);
	for(rint i = head[x], y;i;i = e[i].nxt) {
		if(vis[y = e[i].to]) continue;
		tsiz = siz[y], maxsiz = inf, getrt(y, x);
		Fa[rt] = x;
		solve(rt);
	}
}

ll query(rint opt, rint x, rint l, rint r, ll &ss) {
	rint lef = lower_bound(vec[opt][x].begin(), vec[opt][x].end(), (Node){l, 0}) - vec[opt][x].begin() - 1;
	rint rig = upper_bound(vec[opt][x].begin(), vec[opt][x].end(), (Node){r, 0}) - vec[opt][x].begin() - 1;
	ss = rig - lef;
	ll ans = 0;
	if(rig >= 0 && rig < (int) vec[opt][x].size()) ans += vec[opt][x][rig].sum;
	if(lef >= 0 && lef < (int) vec[opt][x].size()) ans -= vec[opt][x][lef].sum;
	return ans;
}

int main() {
	n = read<int>(), q = read<int>(), A = read<int>();
	for(rint i = 1;i <= n; ++i) v[i] = read<int>();
	for(rint i = 1, x, y, z;i < n; ++i) {
		x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z), add(y, x, z);
	}
	dfs1(1, 0), dfs2(1, 1);
	tsiz = n, maxsiz = inf, getrt(1, 0), solve(rt);
	for(rint i = 1;i <= n; ++i) {
		sort(vec[0][i].begin(), vec[0][i].end());
		sort(vec[1][i].begin(), vec[1][i].end());
		for(rint j = 1;j < (int)vec[0][i].size(); ++j) vec[0][i][j].sum += vec[0][i][j - 1].sum;
		for(rint j = 1;j < (int)vec[1][i].size(); ++j) vec[1][i][j].sum += vec[1][i][j - 1].sum;
	}
	for(rint i = 1, x, l, r;i <= q; ++i) {
		x = read<int>(), l = (read<ll>() + lastans) % A, r = (read<ll>() + lastans) % A;
		l > r ? swap(l, r) : void();
		ll s1, s2;
		lastans = query(0, x, l, r, s1);
		for(rint now = x;Fa[now];now = Fa[now]) {
			lastans += query(0, Fa[now], l, r, s2) - query(1, now, l, r, s1);
			lastans += (s2 - s1) * Dis(x, Fa[now]);
		}
		printf("%lld\n", lastans);
	}
	return 0;
}