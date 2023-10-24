#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
using Edge = pair<int, int>;

const int N = 1e5 + 50, LOG = 20;
int n, m, x, y;
vector<Edge> e[N];
int dep[N], fa[N][20], dis[N];
int log2[N];

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

void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w));
}

void get_log() {
	for (int i = 1; i <= n; i++)
		log2[i] = log2[i - 1] + (1 << log2[i - 1] == i);
	return;
}

void dfs(int u = 1, int from = 0, int val = 0) {
	fa[u][0] = from, dep[u] = dep[from] + 1, dis[u] = val;
	for (int i = 1; i <= log2[dep[u]]; i++) 
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs(v, u, w ^ val);
	}
	return;
}

void init() {
	get_log();
	dfs();
	// cout << 1 << endl;
	return;
}

void solve() {
	read(x, y);
	print(dis[x] ^ dis[y], '\n');
	return;
}

int main() {
	read(n);
	for (int i = 1, u, v, w; i < n; i++) read(u, v, w), add(u, v, w), add(v, u, w);
	init();
	read(m);
	while (m--) {
		solve();
	}
	// print(15004 ^ 9684 ^ 14635 ^ 9644);
	return 0;
}