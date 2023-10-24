#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 1e5 + 50;
int n, m, r, p, a[N], no[N];
int tree[N << 2], lzy[N << 2];
vector<int> e[N];
int fa[N], dep[N], siz[N], son[N], top[N], val[N], cnt;

template<typename T>
void read(T& x) {
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
void read(T& x, args& ... tmp) {
	read(x);
	read(tmp...);
	return;
}

template<typename T>
void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x / 10) print(x / 10);
	putchar(x % 10 + '0');
	return;
}

template<typename T>
void print(T x, char c) {
	print(x), putchar(c);
	return;
}

// HLD

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs1(int u, int from) {
	fa[u] = from, dep[u] = dep[from] + 1, siz[u] = 1;
	for (auto v : e[u]) {
		if (v == from) continue;
		dfs1(v, u), siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
	return;
}

void dfs2(int u, int rt) {
	top[u] = rt, no[u] = ++cnt, a[cnt] = val[u];
	if (son[u]) dfs2(son[u], rt);
	for (auto v : e[u]) {
		if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
	return;
}

// SegTree

void pushup(int u) {
	return (void)(tree[u] = (tree[u << 1] + tree[u << 1 | 1]) % p);
}

void pushdown(int l, int r, int u) {
	if (!lzy[u]) return;
	int mid = (l + r) >> 1, lu = u << 1, ru = u << 1 | 1;
	lzy[lu] += lzy[u], tree[lu] = (tree[lu] + (mid - l + 1) * lzy[u]) % p;
	lzy[ru] += lzy[u], tree[ru] = (tree[ru] + (r - mid) * lzy[u]) % p;
	lzy[u] = 0;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return (void)(tree[u] = a[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int l, int r, int s, int t, int u, int val) {
	if (l <= s && t <= r)
		return (void)(lzy[u] += val, tree[u] = (tree[u] + (t - s + 1) * val) % p);
	int mid = (s + t) >> 1, lu = u << 1, ru = u << 1 | 1;
	pushdown(s, t, u);
	if (l <= mid) modify(l, r, s, mid, lu, val);
	if (r > mid) modify(l, r, mid + 1, t, ru, val);
	pushup(u);
	return;
}

int query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tree[u];
	pushdown(s, t, u);
	int res = 0, mid = (s + t) >> 1, lu = u << 1, ru = u << 1 | 1;
	if (l <= mid) res = (res + query(l, r, s, mid, lu)) % p;
	if (r > mid) res = (res + query(l, r, mid + 1, t, ru)) % p;
	return res;
}

void updateP2P(int x, int y, int val) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		modify(no[top[x]], no[x], 1, n, 1, val), x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	modify(no[x], no[y], 1, n, 1, val);
	return;
}

int queryP2P(int x, int y) {
	int ans = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		ans = (ans + query(no[top[x]], no[x], 1, n, 1)) % p, x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	ans = (ans + query(no[x], no[y], 1, n, 1)) % p;
	return (ans % p);
}

void updateInTree(int x, int val) {
	return (void)(modify(no[x], no[x] + siz[x] - 1, 1, n, 1, val));
}

int queryInTree(int x) {
	return (query(no[x], no[x] + siz[x] - 1, 1, n, 1) % p);
}

int main() {
	read(n, m, r, p);
	for (int i = 1; i <= n; i++) read(val[i]);
	for (int i = 1, u, v; i < n; i++) read(u, v), add(u, v), add(v, u);

	dfs1(r, 0);
	dfs2(r, r);

	// cerr << 1 << endl;

	build(1, n, 1);

	// for (int i = 1; i <= n; i++) cerr << query(i, i, 1, n, 1) << ' ';
	// cerr << endl;

	while (m--) {
		int opt, x, y, z;
		read(opt);
		if (opt == 1) read(x, y, z), updateP2P(x, y, z);
		else if (opt == 2) read(x, y), print(queryP2P(x, y), '\n');
		else if (opt == 3) read(x, z), updateInTree(x, z);
		else read(x), print(queryInTree(x), '\n');
 	}

 	// for (int i = 1; i <= n; i++) cerr << query(i, i, 1, n, 1) << ' ';

	return 0;
}