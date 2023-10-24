#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1e5 + 50;
int n, q;
int cnt, fa[N], dep[N], top[N], son[N], size[N], no[N];
int tree[N << 2], ass[N << 2];
vector<int> e[N];

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

inline void addEdge(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs1(int u) {
	dep[u] = dep[fa[u]] + 1, size[u] = 1;
	for (auto v : e[u]) {
		if (v == fa[u]) continue;
		dfs1(v), size[u] += size[v];
		if (size[v] > size[son[u]]) son[u] = v;
	}
	return;
}

void dfs2(int u, int rt) {
	top[u] = rt, no[u] = ++cnt;
	if (son[u]) dfs2(son[u], rt);
	for (auto v : e[u]) {
		if (v == son[u] || v == fa[u]) continue;
		dfs2(v, v);
	}
}

void pushup(int u) {
	return (void)(tree[u] = tree[u << 1] + tree[u << 1 | 1]);
}

void pushdown(int l, int r, int u) {
	if (ass[u] == -1) return;
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	tree[lc] = (mid - l + 1) * ass[u], ass[lc] = ass[u];
	tree[rc] = (r - mid) * ass[u], ass[rc] = ass[u];
	ass[u] = -1;
}

void modify(int l, int r, int s, int t, int u, int val) {
	if (l <= s && t <= r) return (void)(tree[u] = val * (t - s + 1), ass[u] = val);
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	pushdown(s, t, u);
	if (l <= mid) modify(l, r, s, mid, lc, val);
	if (r > mid) modify(l, r, mid + 1, t, rc, val);
	pushup(u);
	return;
}

int query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tree[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1, res = 0;
	pushdown(s, t, u);
	if (l <= mid) res += query(l, r, s, mid, lc);
	if (r > mid) res += query(l, r, mid + 1, t, rc);
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

void updateInTree(int x, int val) {
	return (void)(modify(no[x], no[x] + size[x] - 1, 1, n, 1, val));
}

int queryP2P(int x, int y) {
	int res = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		res += query(no[top[x]], no[x], 1, n, 1), x= fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	res += query(no[x], no[y], 1, n, 1);
	return res;
}

int queryInTree(int x) {
	return query(no[x], no[x] + size[x] - 1, 1, n, 1);
}

int main() {
	read(n);
	for (int i = 2; i <= n; i++) read(fa[i]), fa[i]++, addEdge(i, fa[i]), addEdge(fa[i], i);
	dfs1(1), dfs2(1, 1);
	memset(ass, -1, sizeof ass);
	read(q);
	while (q--) {
		char opt[15];
		int x;
		scanf("%s", opt), read(x), x++;
		if (opt[0] == 'i') {
			int tmp1 = queryP2P(1, x);
			updateP2P(1, x, 1);
			int tmp2 = queryP2P(1, x);
			// cerr << '#' << tmp1 << ' ' << tmp2 << endl;
			print(tmp2 - tmp1, '\n');
		} else {
			int tmp1 = queryInTree(x);
			updateInTree(x, 0);
			print(tmp1, '\n');
		}
	}
	return 0;
}