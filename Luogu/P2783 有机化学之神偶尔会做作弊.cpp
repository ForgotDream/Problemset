#include <bits/stdc++.h>
#include <cstdint>
#include <memory>

namespace FastIO {
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
using ull = unsigned long long;
using i128 = __int128;

const int N = 1e4 + 50;
int n, m, q;
vector<int> e[N], g[N];
int clk, dfn[N], low[N];
int belong[N], cnt;
stack<int> st;
int fa[N], son[N], dep[N], siz[N], top[N];

inline void add(int u, int v, vector<int> *e) {
	return (void) (e[u].push_back(v));
}

void tarjan(int u, int from) {
	dfn[u] = low[u] = ++clk;
	st.push(u);
	for (int v : e[u]) {
		if (v == from) continue;
		if (!dfn[v]) {
			tarjan(v, u), low[u] = min(low[u], low[v]);
		} else low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		++cnt;
		int p;
		do {
			p = st.top(), st.pop();
			belong[p] = cnt;
		} while (p != u);
	}
	return;
}

void dfs1(int u, int from) {
	fa[u] = from, siz[u] = 1, dep[u] = dep[from] + 1;
	for (int v : g[u]) {
		if (v == from) continue;
		dfs1(v, u), siz[u] += siz[v];
		if (siz[son[u]] < siz[v]) son[u] = v;
	}
	return;
}

void dfs2(int u, int rt) {
	top[u] = rt;
	if (son[u]) dfs2(son[u], rt);
	for (int v : g[u]) {
		if (v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
	return;
}

int getLCA(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) y = fa[top[y]];
		else x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

void out(int num) {
	static char buf[50];
	int cnt = 0;
	while (num) buf[++cnt] = (num & 1) + '0', num >>= 1;
	for (int i = cnt; i; i--) putchar(buf[i]);
	putchar('\n');
	return;
}

int main() {
	read(n, m);
	for (int i = 1, u, v; i <= m; i++)
		read(u, v), add(u, v, e), add(v, u, e);

	tarjan(1, 0);

	for (int u = 1; u <= n; u++) 
		for (int v : e[u]) 
			if (belong[u] != belong[v]) 
				add(belong[u], belong[v], g), add(belong[v], belong[u], g);
	for (int u = 1; u <= cnt; u++) {
		sort(g[u].begin(), g[u].end()); 
		g[u].erase(unique(g[u].begin(), g[u].end()), g[u].end()); 
	}

	dfs1(1, 0), dfs2(1, 1);

	read(q);
	// cerr << belong[1] << ' ' << belong[2] << endl;
	// cerr << getLCA(belong[1], belong[2]) << endl;
	for (int i = 1, x, y; i <= q; i++) {
		read(x, y), x = belong[x], y = belong[y];
		out(dep[x] + dep[y] - 2 * dep[getLCA(x, y)] + 1);
	}
	return 0;
}
