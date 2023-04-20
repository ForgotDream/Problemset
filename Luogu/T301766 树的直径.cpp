#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;
using Edge = pair<int, ll>;

const int N = 2e5 + 50;
ll dis[N], maxx = 0;
int pivot, n;
vector<Edge> e[N]; 

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

inline void add(int u, int v, ll w) {
	return (void)(e[u].emplace_back(v, w));
}

void dfs(int u, int from, int weigh) {
	dis[u] = dis[from] + weigh;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs(v, u, w);
	}
	return;
}

void solve() {
	dfs(1, 0, 0);
	for (int i = 1; i <= n; i++) if (maxx < dis[i]) maxx = dis[i], pivot = i;
	dfs(pivot, 0, 0), maxx = 0;
	for (int i = 1; i <= n; i++) maxx = max(maxx, dis[i]);
	print(maxx, '\n');
	return;
}

int main() {
	read(n);
	for (int i = 1, u, v, w; i < n; i++) read(u, v, w), add(u, v, w), add(v, u, w);
	solve();
	return 0;
}