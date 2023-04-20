#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 1e5 + 50;
int n, q;
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
	read(n, q);
	for (int i = 1, u, v; i < n; i++) read(u, v), add(u, v), add(v, u);

	dfs();

	while (q--) {
		int x1, y1, x2, y2, lca1, lca2;
		read(x1, y1, x2, y2), lca1 = getLCA(x1, y1), lca2 = getLCA(x2, y2);
		if (dis(x1, y1) + dis(x2, y2) >= dis(x1, x2) + dis(y1, y2)) putchar('Y');
		else putchar('N');
		putchar('\n');
	}

	return 0;
}