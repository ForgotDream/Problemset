#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 1e6 + 50;
int n, pivot, maxx, pre;
int dis1[N], dis2[N];
vector<int> e[N];

template<typename T>
inline void read(T& x) {
	x = 0;
	T f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
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

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs1(int u, int from) {
	dis1[u] = dis1[from] + 1;
	for (int v : e[u]) {
		if (v != from) dfs1(v, u);
	}
	return;
}

void dfs2(int u, int from) {
	dis2[u] = dis2[from] + 1;
	for (int v : e[u]) {
		if (v != from) dfs2(v, u);
	}
	return;
}

void solve() {
	dfs1(1, 0);
	for (int i = 1; i <= n; i++) if (maxx < dis1[i]) pivot = i, maxx = dis1[i];
	dfs1(pivot, 0), pre = pivot, maxx = 0;
	for (int i = 1; i <= n; i++) if (maxx < dis1[i]) pivot = i, maxx = dis1[i];
	dfs2(pivot, 0);
	for (int i = 1; i <= n; i++) print(max(dis1[i] - 1, dis2[i] - 1), '\n');
	return;
}

int main() {
	read(n);
	for (int i = 1, u, v; i < n; i++) read(u, v), add(u, v), add(v, u);
	solve();
	return 0;
}