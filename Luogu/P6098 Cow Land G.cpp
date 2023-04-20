#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;

const int N = 1e5 + 50;
vector<int> e[N];
int n, q;
int cnt, no[N], fa[N], son[N], top[N], dep[N], size[N], val[N];
ll tree[N << 2], newVal[N];

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

inline void addEdge(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs1(int u, int from) {
	fa[u] = from, dep[u] = dep[from] + 1, size[u] = 1;
	for (auto v : e[u]) {
		if (v == from) continue;
		dfs1(v, u), size[u] += size[v];
		if (size[v] > size[son[u]]) son[u] = v;
	}
	return;
}

void dfs2(int u, int rt) {
	top[u] = rt, no[u] = ++cnt, newVal[cnt] = val[u];
	if (son[u]) dfs2(son[u], rt);
	for (auto v : e[u]) {
		if (v == son[u] || v == fa[u]) continue;
		dfs2(v, v);
	}
	return;
}

inline void pushup(int u) {
	return (void)(tree[u] = tree[u << 1] ^ tree[u << 1 | 1]);
}

void build(int l, int r, int u) {
	if (l == r) return (void)(tree[u] = newVal[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void update(int l, int s, int t, int u, ll val) {
	if (l == s && t == l) return (void)(tree[u] = val);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	if (l <= mid) update(l, s, mid, lc, val);
	if (l > mid) update(l, mid + 1, t, rc, val);
	pushup(u);
	return;
}

ll query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tree[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	ll res = 0;
	if (l <= mid) res ^= query(l, r, s, mid, lc);
	if (r > mid) res ^= query(l, r, mid + 1, t, rc);
	return res;
}

void updateSinglePoint(int x, ll val) {
	return (void)(update(no[x], 1, n, 1, val));
}

ll queryP2P(int x, int y) {
	ll res = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		res ^= query(no[top[x]], no[x], 1, n, 1), x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	res ^= query(no[x], no[y], 1, n, 1);
	return res;
}

int main() {
	read(n, q);
	for (int i = 1; i <= n; i++) read(val[i]);
	for (int i = 1, u, v; i < n; i++) read(u, v), addEdge(u, v), addEdge(v, u);
	dfs1(1, 0), dfs2(1, 1), build(1, n, 1);
	while (q--) {
		int opt, x;
		ll y;
		read(opt, x, y);
		if (opt == 1) updateSinglePoint(x, y);
		else print(queryP2P(x, y), '\n');
	}
	return 0;
}