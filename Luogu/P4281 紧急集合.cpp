#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 5e5 + 50, INF = 0x3f3f3f3f;
int n, m;
vector<int> e[N];
int dep[N], fa[N][25];

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

void dfs(int u = 1, int from = 0) {
	dep[u] = dep[from] + 1, fa[u][0] = from;
	for (int i = 1; (1 << i) <= dep[u]; i++)
		fa[u][i] =  fa[fa[u][i - 1]][i - 1];
	for (auto v : e[u]) {
		if (v == from) continue;
		dfs(v, u);
	}
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

int dis(int x, int y) {
	return dep[x] + dep[y] - 2 * dep[getLCA(x, y)];
}

int main() {
	read(n, m);
	for (int i = 1, u, v; i < n; i++) read(u, v), add(u, v), add(v, u);

	dfs();

	while (m--) {
		int x, y, z, lca1, lca2, lca3, lca;
		read(x, y, z);
		lca1 = getLCA(x, y), lca2 = getLCA(y, z), lca3 = getLCA(x, z);
		if (lca1 == lca2) lca = lca3;
		else if (lca2 == lca3) lca = lca1;
		else lca = lca2;
		print(lca, ' '), print(dep[x] + dep[y] + dep[z] - dep[lca1] - dep[lca2] - dep[lca3], '\n');
	}

	return 0;
}