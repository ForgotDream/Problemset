#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 1e5 + 50;
int n, m, x, y;
char type[N], pref;
vector<int> e[N];
int h[N], g[N];
int fa[N][25], dep[N];
char s[N];

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
	h[u] = (type[u] == 'H') + h[from], g[u] = (type[u] == 'G') + g[from];
	// cout << h[u] << ' ' << g[u] << endl;
	fa[u][0] = from, dep[u] = dep[from] + 1;
	for (int i = 1; (1 << i) <= dep[u]; i++) 
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (auto v : e[u]) {
		if (v == from) continue;
		dfs(v, u);
	}
	return;
}

void init() {
	dfs();
	return;
}

int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 20; i >= 0; i--) 
		if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; i--) 
		if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void solve() {
	read(x, y);
	pref = getchar();
	while (pref != 'H' && pref != 'G') pref = getchar();
	int u = lca(x, y);
	// cout << u << ' ';
	int tmp;
	if (pref == 'G') {
		tmp = g[x] + g[y] - g[u] - g[fa[u][0]];
		// cerr << "# " << tmp << endl;
	} else {
		tmp = h[x] + h[y] - h[u] - h[fa[u][0]];
		// cerr << "$ " << tmp << endl;
	}
	return (void)(tmp ? print(1) : print(0));
}

int main() {
	read(n, m);
	scanf("%s", s + 1);
	for (int i = 1; i <= n; i++) type[i] = s[i];
	for (int i = 1, u, v; i < n; i++) read(u, v), add(u, v), add(v, u);
	init();
	while (m--) {
		solve();
	}
	return 0;
}