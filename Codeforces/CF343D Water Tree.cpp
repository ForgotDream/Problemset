#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int N = 5e5 + 50;
int n, m;
int opt, x;
vector<int> e[N];
int fa[N], son[N], size[N], dep[N], no[N], top[N], tclock;
int tree[N << 2], ass[N << 2];

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
	top[u] = rt, no[u] = ++tclock;
	if (son[u]) dfs2(son[u], rt);
	for (auto v : e[u]) {
		if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
	return;
}

inline void pushdown(int u) {
	if (~ass[u]) 
		tree[u << 1] = ass[u << 1] = ass[u], tree[u << 1 | 1] = ass[u << 1 | 1] = ass[u], ass[u] = -1;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return;
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	return;
}

int query(int target, int s, int t, int u) {
	if (s == target && target == t) return tree[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(u);
	if (target <= mid) return query(target, s, mid, lc);
	else return query(target, mid + 1, t, rc);
}

void assign(int l, int r, int s, int t, int u, int val) {
	if (l <= s && t <= r) return (void)(tree[u] = ass[u] = val);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(u);
	if (l <= mid) assign(l, r, s, mid, lc, val);
	if (r > mid) assign(l, r, mid + 1, t, rc, val);
	return;
}

int querySinglePoint(int x) {
	return query(no[x], 1, n, 1);
}

void UpdateP2P(int x, int y, int val) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		assign(no[top[x]], no[x], 1, n, 1, val), x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	assign(no[x], no[y], 1, n, 1, val);
	return;
}

void updateInTree(int x, int val) {
	return (void)(assign(no[x], no[x] + size[x] - 1, 1, n, 1, val));
}

int main() {
	memset(ass, -1, sizeof ass);
	read(n);
	for (int i = 1, u, v; i < n; i++) read(u, v), addEdge(u, v), addEdge(v, u);
	dfs1(1, 0), dfs2(1, 1), build(1, n, 1);
	read(m);
	while (m--) {
		read(opt, x);
		if (opt == 1) updateInTree(x, 1);
		else if (opt == 2) UpdateP2P(1, x, 0);
		else print(querySinglePoint(x), '\n');
	}
	return 0;
}