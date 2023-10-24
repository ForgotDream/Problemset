#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 3e5 + 50;
int n;
vector<int> e[N];
int d[N], dep[N], fa[N][25];
int x, y, lca, ans, order[N];

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

void dfs1(int u = 1, int from = 0) {
	dep[u] = dep[from] + 1, fa[u][0] = from;
	for (int i = 1; (1 << i) <= dep[u]; i++)
		fa[u][i] =  fa[fa[u][i - 1]][i - 1];
	for (auto v : e[u]) {
		if (v == from) continue;
		dfs1(v, u);
	}
	return;
}

void dfs2(int u = 1, int from = 0) {
	for (auto v : e[u]) {
		if (v == from) continue;
		dfs2(v, u);
		d[u] += d[v];
	}
	ans = max(ans, d[u]);
	return;
}

void init() {
	dfs1();
	return;
}

int getLCA(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 20; i >= 0; i--) 
		if (dep[x] - (1 << i) >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; i--) 
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

int main() {
	read(n);
	for (int i = 1; i <= n; i++) read(order[i]);
	for (int i = 1, u, v; i < n; i++) read(u, v), add(u, v), add(v, u);
	init();
	for (int i = 1; i < n; i++) {
		lca = getLCA(order[i], order[i + 1]);
		d[order[i]]++, d[order[i + 1]]++, d[lca]--, d[fa[lca][0]]--;
	}
	dfs2();
	// print(ans, '\n');
	for (int i = 2; i <= n; i++) d[order[i]]--;
	for (int i = 1; i <= n; i++) print(d[i], '\n');
	return 0;
}