#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
using Edge = pair<int, int>;

const int N = 1e5 + 50, INF = 0x3f3f3f3f;
vector<Edge> e[N];
int n, k;
int dis[N], nxt[N];
int dis2[N], ans = 0;
bool vis[N];

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

inline void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w));
}

void dfs(int u, int from, int d) {
	dis[u] = dis[from] + d, nxt[u] = from;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs(v, u, w);
	}
}

void dp(int u) {
	vis[u] = true;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (vis[v]) continue;
		// cerr << u << ' ' << v << ' ' << w << endl;
		dp(v), ans = max(ans, dis2[u] + dis2[v] + w);
		dis2[u] = max(dis2[u], dis2[v] + w);
	}
	return;
}

void solve() {
	int L, R, maxx = -INF;
	dfs(1, 0, 0);
	for (int i = 1; i <= n; i++) if (maxx < dis[i]) L = i, maxx = dis[i];
	dis[L] = 0, dfs(L, 0, 0), maxx = -INF;
	for (int i = 1; i <= n; i++) if (maxx < dis[i]) R = i, maxx = dis[i];
	if (k == 1) {
		print(2 * n - dis[R] - 1, '\n');
	} else {
		for (int i = R; nxt[i]; i = nxt[i]) {
			// cerr << i << ' ' << nxt[i] << endl;
			for (auto &j : e[i]) {
				int v = j.first;
				if (v == nxt[i]) {
					j.second = -1;
					break;
				}
			}
			for (auto &j : e[nxt[i]]) {
				int v = j.first;
				if (v == i) {
					j.second = -1;
					break;
				}
			}
		}
		// memset(dis2, -0x3f, sizeof dis2);
		dp(1);
		// cerr << dis[R] << endl << ans << endl;
		print(2 * n - ans - dis[R], '\n');
	}
	return;
}

int main() {
	read(n, k);
	for (int i = 1, u, v; i < n; i++) read(u, v), add(u, v, 1), add(v, u, 1);
	solve();
	return 0;
}