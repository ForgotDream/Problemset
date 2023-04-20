#include <bits/stdc++.h>

namespace FastIO {
	char buf[1 << 23], *p1 = buf, *p2 = buf;

	inline char gc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
	}

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

const int N = 3e5 + 50;
int n, m;
vector<int> e[N], g[N];
int clk, dfn[N], low[N];
stack<int> s;
bool ins[N];
int dccCnt, belong[N];
int dis[N], pivot;

inline void add(int u, int v, vector<int> *e) {
	return (void)(e[u].push_back(v));
}

void tarjan(int u, int from) {
	dfn[u] = low[u] = ++clk, s.push(u);
	for (auto v : e[u]) {
		if (v == from) continue;
		if (!dfn[v]) tarjan(v, u), low[u] = min(low[u], low[v]);
		else if (!ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		dccCnt++;
		int p;
		do {
			p = s.top(), s.pop();
			ins[p] = false, belong[p] = dccCnt;
		} while (p != u);
	}
	return;
}

void dfs(int u, int from) {
	dis[u] = dis[from] + 1;
	for (int v : g[u]) {
		if (v == from) continue;
		dfs(v, u);
	}
	return;
}

int main() {
	read(n, m);
	for (int i = 1, u, v; i <= m; i++) 
		read(u, v), add(u, v, e), add(v, u, e);
	
	tarjan(1, 0);

	for (int u = 1; u <= n; u++) 
		for (int v : e[u]) 
			if (belong[u] != belong[v]) add(belong[u], belong[v], g), add(belong[v], belong[u], g);
	for (int u = 1; u <= n; u++) 
		sort(g[u].begin(), g[u].end()), g[u].erase(unique(g[u].begin(), g[u].end()), g[u].end());

	dfs(belong[1], 0);
	for (int i = 1; i <= dccCnt; i++) if (dis[pivot] < dis[i]) pivot = i;
	dis[pivot] = 0, dfs(pivot, 0);
	for (int i = 1; i <= dccCnt; i++) if (dis[pivot] < dis[i]) pivot = i;

	print(dis[pivot] - 1, '\n');
	return 0;
}
