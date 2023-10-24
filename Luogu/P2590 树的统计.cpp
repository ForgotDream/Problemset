#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 3e4 + 50, INF = 0x3f3f3f3f;
int n, m;
vector<int> e[N];
int cnt, val[N], top[N], size[N], no[N], son[N], fa[N], dep[N];
int sum[N << 2], maxx[N << 2], ass[N << 2], newVal[N << 2];

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

void addEdge(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs1(int u, int from) {
	size[u] = 1, dep[u] = dep[from] + 1, fa[u] = from;
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

void pushup(int u) {
	int lc = u << 1, rc = u << 1 | 1;
	sum[u] = sum[lc] + sum[rc], maxx[u] = max(maxx[lc], maxx[rc]);
	return;
}

void pushdown(int l, int r, int u) {
	if (!ass[u]) return;
	int lc = u << 1, rc = u << 1 | 1, mid = (l + r) >> 1;
	ass[lc] = ass[u], sum[lc] = (mid - l + 1) * ass[u], maxx[lc] = ass[u];
	ass[rc] = ass[u], sum[rc] = (r - mid) * ass[u], maxx[rc] = ass[u];
	ass[u] = 0;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return (void)(sum[u] = maxx[u] = newVal[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int l, int r, int s, int t, int u, int val) {
	if (l <= s && t <= r) 
		return (void)(ass[u] = val, sum[u] = (t - s + 1) * val, maxx[u] = val);
	int mid  = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(s, t, u);
	if (l <= mid) modify(l, r, s, mid, lc, val);
	if (r > mid) modify(l, r, mid + 1, t, rc, val);
	pushup(u);
	return;
}

int querySum(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return sum[u];
	int mid  = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = 0;
	pushdown(s, t, u);
	if (l <= mid) res += querySum(l, r, s, mid, lc);
	if (r > mid) res += querySum(l, r, mid + 1, t, rc);
	return res;
}

int queryMax(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return maxx[u];
	int mid  = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = -INF;
	pushdown(s, t, u);
	if (l <= mid) res = max(res, queryMax(l, r, s, mid, lc));
	if (r > mid) res = max(res, queryMax(l, r, mid + 1, t, rc));
	return res;	
}

void modify(int x, int val) {
	return (void)(modify(no[x], no[x], 1, n, 1, val));
}

int querySum(int x, int y) {
	int res = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		res += querySum(no[top[x]], no[x], 1, n, 1), x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	res += querySum(no[x], no[y], 1, n, 1);
	return res;
}

int queryMax(int x, int y) {
	int res = -INF;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		res = max(res, queryMax(no[top[x]], no[x], 1, n, 1)), x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	res = max(res, queryMax(no[x], no[y], 1, n, 1));
	return res;
}

int main() {
	read(n);
	for (int i = 1, u, v; i < n; i++) read(u, v), addEdge(u, v), addEdge(v, u);
	for (int i = 1; i <= n; i++) read(val[i]);
	dfs1(1, 0), dfs2(1, 1);
	build(1, n, 1);
	// for (int i = 1; i <= n; i++) cerr << queryMax(i, i, 1, n, 1) << ' ';
	// cerr << endl;
	read(m);
	while (m--) {
		char opt[10];
		int x, y;
		// cerr << '#' << m << endl;
		scanf("%s", opt), read(x, y);
		if (opt[1] == 'H') modify(x, y);
		else if (opt[1] == 'M') print(queryMax(x, y), '\n');
		else print(querySum(x, y), '\n');
	}
	return 0;
}