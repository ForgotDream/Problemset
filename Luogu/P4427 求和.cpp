#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;

const int N = 3e5 + 50;
const ll MOD = 998244353;
int n, m;
vector<int> e[N];
int fa[N][21], dep[N];
ll sum[N][51];

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

ll fastPower(ll base, ll p, ll m) {
	ll res = 1;
	while (p) {
		if (p & 1) res = (res * base) % m;
		base = (base * base) % m;
		p >>= 1;
	}
	return res;
}

void dfs(int u = 1, int from = 1) {
	dep[u] = dep[from] + 1, fa[u][0] = from;
	for (int i = 0; i <= 50; i++) sum[u][i] = (sum[from][i] + fastPower((ll)dep[u], i, MOD)) % MOD;
	for (int i = 1; (1 << i) <= dep[u]; i++) fa[u][i] =  fa[fa[u][i - 1]][i - 1];
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

int main() {
	read(n);
	for (int i = 1, u, v; i < n; i++) read(u, v), add(u, v), add(v, u);

	dep[1] = -1;
	dfs();

	read(m);
	while (m--) {
		int x, y, k, lca;
		read(x, y, k);
		lca = getLCA(x, y);
		// print(sum[x][k], '\n');
		print((sum[x][k] + sum[y][k] - sum[fa[lca][0]][k] - sum[lca][k] + 10 * MOD) % MOD, '\n');
	}

	return 0;
}