#include <bits/stdc++.h>

namespace FastIO{
	template<typename T>
	inline void read(T& x) {
		x = 0;
		T f = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
		x *= f;
		return;
	}

	template<typename T, typename ... args>
	inline void read(T& x, args& ... tmp) {
		read(x);
		read(tmp...);
		return;
	}

	template<typename T>
	inline void print(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x / 10) print(x / 10);
		putchar(x % 10 + '0');
		return;
	}

	template<typename T>
	inline void print(T x, char c) {
		print(x), putchar(c);
		return;
	}
}

using namespace std;
using namespace FastIO;
using ll = long long;

const int N = 2e5 + 50, INF = 0x7f7f7f7f;
int n, m;
struct Edge {
	int v, w, no;
	Edge(int v, int w, int no) : v(v), w(w), no(no) {};
};
vector<Edge> e[N];
int edgeCnt, belong[N];
int siz[N], son[N], fa[N], dep[N], top[N], val[N], no[N], newVal[N], cnt;
int sum[N << 2], maxx[N << 2], minn[N << 2], rev[N << 2];

inline void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w, ++edgeCnt), e[v].emplace_back(u, w, edgeCnt));
}

void dfs1(int u, int from) {
	siz[u] = 1, dep[u] = dep[from] + 1, fa[u] = from;
	for (auto i : e[u]) {
		int v = i.v, w = i.w;
		if (v == from) continue;
		belong[i.no] = v, val[v] = w, dfs1(v, u), siz[u] += siz[v];
		if (siz[son[u]] < siz[v]) son[u] = v;
 	}
	return;
}

void dfs2(int u, int rt) {
	top[u] = rt, no[u] = ++cnt, newVal[cnt] = val[u];
	if (son[u]) dfs2(son[u], rt);
	for (auto i : e[u]) {
		int v = i.v;
		if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
	return;
}

inline void pushup(int u) {
	int lc = u << 1, rc = u << 1 | 1;
	sum[u] = sum[lc] + sum[rc]; 
	maxx[u] = max(maxx[lc], maxx[rc]), minn[u] = min(minn[lc], minn[rc]);
	return;
}

inline void pushdown(int u) {
	if (!rev[u]) return;
	int lc = u << 1, rc = u << 1 | 1;
	sum[lc] *= -1, sum[rc] *= -1;
	swap(maxx[lc], minn[lc]), swap(maxx[rc], minn[rc]);
	maxx[lc] *= -1, minn[lc] *= -1, maxx[rc] *= -1, minn[rc] *= -1;
	rev[lc] ^= 1, rev[rc] ^= 1, rev[u] = 0;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return (void)(sum[u] = maxx[u] = minn[u] = newVal[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int target, int s, int t, int u, int num) {
	if (s == target && target == t) return (void)(sum[u] = maxx[u] = minn[u] = num);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(u);
	if (target <= mid) modify(target, s, mid, lc, num);
	else modify(target, mid + 1, t, rc, num);
	pushup(u);
	return;
}

void reverse(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) {
		sum[u] *= -1, swap(maxx[u], minn[u]), maxx[u] *= -1, minn[u] *= -1, rev[u] ^= 1;
		return;
	}
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(u);
	if (l <= mid) reverse(l, r, s, mid, lc);
	if (r > mid) reverse(l, r, mid + 1, t, rc);
	pushup(u);
	return;
}

int querySum(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return sum[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = 0;
	pushdown(u);
	if (l <= mid) res += querySum(l, r, s, mid, lc);
	if (r > mid) res += querySum(l, r, mid + 1, t, rc);
	return res;
}

int queryMax(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return maxx[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = -INF;
	pushdown(u);
	if (l <= mid) res = max(res, queryMax(l, r, s, mid, lc));
	if (r > mid) res = max(res, queryMax(l, r, mid + 1, t, rc));
	return res;
}

int queryMin(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return minn[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = INF;
	pushdown(u);
	if (l <= mid) res = min(res, queryMin(l, r, s, mid, lc));
	if (r > mid) res = min(res, queryMin(l, r, mid + 1, t, rc));
	return res;
}

int querySumP2P(int u, int v) {
	int res = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		res += querySum(no[top[u]], no[u], 1, n, 1), u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	res += querySum(no[u] + 1, no[v], 1, n, 1);
	return res;
}

int queryMaxP2P(int u, int v) {
	int res = -INF;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		res = max(res, queryMax(no[top[u]], no[u], 1, n, 1)), u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	res = max(res, queryMax(no[u] + 1, no[v], 1, n, 1));
	return res;
}

int queryMinP2P(int u, int v) {
	int res = INF;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		res = min(res, queryMin(no[top[u]], no[u], 1, n, 1)), u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	res = min(res, queryMin(no[u] + 1, no[v], 1, n, 1));
	return res;
}

void modifySinglePoint(int u, int num) {
	modify(no[belong[u]], 1, n, 1, num);
	return;
}

void reverseP2P(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		reverse(no[top[u]], no[u], 1, n, 1), u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	reverse(no[u] + 1, no[v], 1, n, 1);
	return;
}

void debug() {
	for (int i = 1; i <= n; i++) cerr << no[i] << ' ';
	cerr << endl;
	cerr << querySumP2P(2, 3) << endl;
	// cerr << sum[1] << endl;
	for (int i = 1; i <= n; i++) cerr << newVal[no[i]] << ' ';
	cerr << endl;
	for (int i = 1; i < n; i++) cerr << i << " belongs to " << belong[i] << endl;
	// cerr << edgeCnt << endl; 
	// assert(n == cnt);
	return;
}

int main() {
	// freopen("P1505_1.in", "r", stdin);
	// freopen("1.txt", "w", stdout); 
	read(n);
	for (int i = 1, u, v, w; i < n; i++) 
		read(u, v, w), add(u + 1, v + 1, w);

	dfs1(1, 0), dfs2(1, 1);
	build(1, n, 1);

	// debug();

	read(m);
	while (m--) {
		int u, v;
		char opt[10];
		scanf("%s", opt);
		// cout << "in: " << m << ' ' << opt << endl;
		read(u, v), u++, v++;
		// cout << u << ' ' << v << endl;
		if (opt[0] == 'C') u--, v--, modifySinglePoint(u, v);
		else if (opt[0] == 'N') reverseP2P(u, v);
		else if (opt[0] == 'S') print(querySumP2P(u, v), '\n');
		else if (opt[1] == 'A') print(queryMaxP2P(u, v), '\n');
		else print(queryMinP2P(u, v), '\n');
		// cout << "out." << endl;
	}
	// cout << "#" << sum[1] << endl;
	return 0;
}
