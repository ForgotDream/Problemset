#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;

const int N = 1e5 + 50;
vector<int> e[N];
int n, m;
int val[N], fa[N], top[N], son[N], size[N], dep[N], cnt;
int newVal[N], no[N];
ll add[N << 2], tree[N << 2];

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
	fa[u] = from, size[u] = 1, dep[u] = dep[from] + 1;
	for (auto v : e[u]) {
		if (v == from) continue;
		dfs1(v, u);
		size[u] += size[v];
		if (size[v] > size[son[u]]) son[u] = v;
	}
	return;
}

void dfs2(int u, int rt) {
	top[u] = rt, no[u] = ++cnt, newVal[cnt] = val[u];
	if (son[u]) dfs2(son[u], rt);
	for (int v : e[u]) {
		if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
	return;
}

void pushup(int u) {
	return (void)(tree[u] = tree[u << 1] + tree[u << 1 | 1]);
}

void pushdown(int l, int r, int u) {
	if (!add[u]) return;
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	tree[lc] += (mid - l + 1) * add[u], add[lc] += add[u];
	tree[rc] += (r - mid) * add[u], add[rc] += add[u];
	add[u] = 0;
	return;
}

void build(int l, int r, int u) {
	if (l == r) return (void)(tree[u] = newVal[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

void modify(int l, int r, int s, int t, int u, ll val) {
	if (l <= s && t <= r) return (void)(tree[u] += (t - s + 1) * val, add[u] += val);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(s, t, u);
	if (l <= mid) modify(l, r, s, mid, lc, val);
	if (r > mid) modify(l, r, mid + 1, t, rc, val);
	pushup(u);
	return;
}

ll query(int l, int r, int s, int t, int u) {
	// cerr << '$' << l << ' ' << r << ' ' << s << ' ' << t << endl;
	if (l <= s && t <= r) return tree[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	ll res = 0;
	pushdown(s, t, u);
	if (l <= mid) res += query(l, r, s, mid, lc);
	if (r > mid) res += query(l, r, mid + 1, t, rc);
	return res;
}

void modifyP2P(int x, int y, int num) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		modify(no[top[x]], no[x], 1, n, 1, num), x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	modify(no[x], no[y], 1, n, 1, num);
	return;
}

ll queryInTree(int x) {
	return query(no[x], no[x] + size[x] - 1, 1, n, 1);
}

int main() {
	read(n);
	for (int i = 1, u, v; i < n; i++) 
		read(u, v), addEdge(u + 1, v + 1), addEdge(v + 1, u + 1), fa[v + 1] = u + 1;
	int i = 1;	
	while (fa[i]) i = fa[i];
	dfs1(i, 0), dfs2(i, i), build(1, 1, n);
	read(m);
	while (m--) {
		char opt[5];
		int x, y, z;
		scanf("%s", opt);
		if (opt[0] == 'A') read(x, y, z), modifyP2P(x + 1, y + 1, z);
		else read(x), print(queryInTree(x + 1), '\n');
	}
	return 0;
}