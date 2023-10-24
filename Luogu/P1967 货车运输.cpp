#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e5 + 50, M = 1e5 + 50;
int n, m, q, x, y;
vector<int> e[N];
int all, fa[N], cnt;
int val[N], son[N], vis[N], ffa[N];
int size[N], dep[N], rt[N];

struct Edge {
	int u, v, w;
	bool operator<(const Edge& oth) const {
		return w > oth.w;
	}
} edge[M];

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

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

int get(int u) {
	return u == fa[u] ? u : fa[u] = get(fa[u]);
}

void dfs1(int u, int from) {
	size[u] = 1, dep[u] = dep[from] + 1, ffa[u] = from, vis[u] = true;
	for (auto v : e[u]) {
		if (v == from) continue;
		dfs1(v, u);
		size[u] += size[v];
		if (size[v] > size[son[u]]) son[u] = v;
	}
	return;
}

void dfs2(int u, int root) {
	rt[u] = root;
	if (son[u]) dfs2(son[u], root);
	for (auto v : e[u]) {
		if (v == son[u] || v == ffa[u]) continue;
		dfs2(v, v);
	}
	return;
}

void kruskal() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	sort(edge + 1, edge + m + 1);
	for (int i = 1; i <= m; i++) {
		int w = edge[i].w, fau = get(edge[i].u), fav = get(edge[i].v);
		// cerr << all << endl;
		if (fau != fav) {
			val[++cnt] = w;
			fa[fau] = fa[fav] = fa[cnt] = cnt;
			add(fau, cnt), add(cnt, fau);
			add(fav, cnt), add(cnt, fav);
		}
		// cerr << all << endl;
	}
	return;
}

int getLCA(int x, int y) {
	while (rt[x] != rt[y])
		if (dep[rt[x]] > dep[rt[y]]) x = ffa[rt[x]];
		else y = ffa[rt[y]];
	return dep[x] > dep[y] ? y : x;
}

void solve() {
	kruskal();
	for (int i = 1; i <= cnt; i++) if (!vis[i]) {
			int f = get(i);
			dfs1(f, 0), dfs2(f, f);
		}
	read(q);
	while (q--) {
		read(x, y);
		if (get(x) != get(y)) print(-1, '\n');
		else print(val[getLCA(x, y)], '\n');
	}
	return;
}

int main() {
	read(n, m), cnt = n;
	for (int i = 1; i <= m; i++) read(edge[i].u, edge[i].v, edge[i].w);
	solve();
	return 0;
}