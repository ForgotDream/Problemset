#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int N = 1e5 + 50, INF = 0x3f3f3f3f;
vector<int> e[N];
int n, q, val[N], newVal[N];
int cnt, no[N], fa[N], son[N], size[N], dep[N], top[N];
int tree[N << 2], add[N << 2], ass[N << 2];
char opt[15];
int x, y, z;

struct Edge {
	int u, v, w;
} edge[N];

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
	return (void)(tree[u] = max(tree[u << 1], tree[u << 1 | 1]));
}

inline void getAssigned(int u) {
	int lc = u << 1, rc = u << 1 | 1;
	if (ass[u] != -1) {
		tree[lc] = ass[u], ass[lc] = ass[u], add[lc] = 0;
		tree[rc] = ass[u], ass[rc] = ass[u], add[rc] = 0;
		ass[u] = -1;
	}
	return;
}

inline void getAdded(int u) {
	int lc = u << 1, rc = u << 1 | 1;
	if (add[u]) {
		tree[lc] += add[u], add[lc] += add[u];
		tree[rc] += add[u], add[rc] += add[u];
		add[u] = 0;
	}
	return;
}

inline void pushdown(int u) {
	int lc = u << 1, rc = u << 1 | 1;
	getAssigned(u), getAdded(u);
	return;
}

void build(int l ,int r, int u) {
	if (l == r) return (void)(tree[u] = newVal[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void assign(int l, int r, int s, int t, int u, int val) {
	if (l <= s && t <= r) return (void)(add[u] = 0, ass[u] = val, tree[u] = val);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(u);
	if (l <= mid) assign(l, r, s, mid, lc, val);
	if (r > mid) assign(l, r, mid + 1, t, rc, val);
	pushup(u);
	return;
}

void modify(int l, int r, int s, int t, int u, int val) {
	if (l <= s && t <= r) return (void)(add[u] += val, tree[u] += val);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(u);
	if (l <= mid) modify(l, r, s, mid, lc, val);
	if (r > mid) modify(l, r, mid + 1, t, rc, val);
	pushup(u);
	return;
}

int query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tree[u];
	int mid = (s + t) >>1, lc = u << 1, rc = u << 1 | 1, res = 0;
	pushdown(u);
	if (l <= mid) res = max(res, query(l, r, s, mid, lc));
	if (r > mid) res = max(res, query(l, r, mid + 1, t, rc));
 	return res;
}

void assignP2P(int x, int y, int val) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		assign(no[top[x]], no[x], 1, n, 1, val), x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	assign(no[x] + 1, no[y], 1, n, 1, val);
	return;
}

void addP2P(int x, int y, int val) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		modify(no[top[x]], no[x], 1, n, 1, val), x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	modify(no[x] + 1, no[y], 1, n, 1, val);
	return;
}

int queryP2P(int x, int y) {
	int res = -INF;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		res = max(res, query(no[top[x]], no[x], 1, n, 1)), x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	res = max(res, query(no[x] + 1, no[y], 1, n, 1));
	return res;
}

int main() {
	memset(ass, -1, sizeof ass);
	read(n);
	for (int i = 1; i < n; i++) 
		read(edge[i].u, edge[i].v, edge[i].w), addEdge(edge[i].u, edge[i].v), addEdge(edge[i].v, edge[i].u);
	dfs1(1, 0);
	for (int i = 1; i < n; i++) {
		int u = edge[i].u, v = edge[i].v, w = edge[i].w;
		if (dep[u] > dep[v]) val[u] = w;
		else val[v] = w;
	}
	dfs2(1, 1);
	build(1, n, 1);
	scanf("%s", opt);
	while (opt[0] != 'D') {
		if (opt[0] == 'C') {
			read(x, z);
			x = dep[edge[x].u] > dep[edge[x].v] ? edge[x].u : edge[x].v;
			assign(no[x], no[x], 1, n, 1, z);
		}
		else read(x, y), print(queryP2P(x, y), '\n');
		scanf("%s", opt);
	}
 	return 0;
}