#include <bits/stdc++.h>
#define int long long

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
using Edge = pair<int, int>;

const int N = 5e5 + 50;
int n, k;
bool bucket[N];
vector<Edge> e[N];
int f[N][2], siz[N], g[N][3], maxx[N];

inline void add(int u, int v, int w) {
	return (void) (e[u].emplace_back(v, w));
}

void dfs1(int u, int from) {
	if (bucket[u]) siz[u] = 1;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		if (siz[v]) {
			g[u][0] += g[v][0] + 2 * w;
			if (f[u][0] < f[v][0] + w) f[u][1] = f[u][0], f[u][0] = f[v][0] + w, maxx[u] = v; 
			else if (f[u][1] < f[v][0] + w) f[u][1] = f[v][0] + w;
 		}
	}
	return;
}

void dfs2(int u, int from) {
	if (u == 1) g[u][1] = g[u][0];
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		if (k == siz[v]) g[v][1] = g[v][0], g[v][2] = f[v][0];
		else if (!siz[v]) g[v][1] = g[u][1] + 2 * w, g[v][2] = max(g[u][2], f[u][0]) + w;
		else {
			g[v][1] = g[u][1];
			if (maxx[u] == v) g[v][2] = max(g[u][2], f[u][1]) + w;
			else g[v][2] = max(g[u][2], f[u][0]) + w;
		}
		dfs2(v, u);
	}
	return;
}

signed main() {
	// 虽然 define int long long 不安全，但是我懒
	read(n, k);
	for (int i = 1, u, v, w; i < n; i++)
		read(u, v, w), add(u, v, w), add(v, u, w);
	for (int i = 1, j; i <= k; i++) read(j), bucket[j] = true;

	dfs1(1, 0), dfs2(1, 0);
	for (int i = 1; i <= n; i++) print(g[i][1] - max(f[i][0], g[i][2]), '\n');
	return 0;
}
