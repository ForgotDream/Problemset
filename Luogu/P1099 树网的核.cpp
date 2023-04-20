#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
using Edge = pair<int, int>;

const int N = 305;
int n, s, dis[N], nxt[N], dis1[N];
bool vis[N];
vector<Edge> e[N];
int L, R, maxx;

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

void dfs(int u, int from) {
	nxt[u] = from;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dis[v] = dis[u] + w;
		dfs(v, u);
	}
	return;
}

void dfs1(int u, int from) {
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		// cerr << u << ' ' << v << ' ' << vis[v] << endl;
		if (vis[v] || v == from) continue;
		dis1[v] = dis1[u] + w;
		// cerr << u << ' ' << v << endl;
		dfs1(v, u);
	}
	return;
}

void solve() {
	dfs(1, 0);
	for (int i = 1; i <= n; i++) if (maxx < dis[i]) L = i, maxx = dis[i];
	dis[L] = 0, dfs(L, 0), maxx = 0;
	for (int i = 1; i <= n; i++) if (maxx < dis[i]) R = i, maxx = dis[i];
 	// cerr << L << ' ' << R << endl;
	int j = R, ans = 0x7fffffff;
	for (int i = R; i; i = nxt[i]) {
		while (nxt[j] && dis[i] - dis[nxt[j]] <= s) j = nxt[j];
		ans = min(ans, max(dis[j], dis[R] - dis[i])), vis[i] = true;
	}
	// memset(dis, 0, sizeof dis);
	for (int i = R; i; i = nxt[i]) dis1[i] = 0, dfs1(i, 0);
	// for (int i = 1; i <= n; i++) cout << dis[i] << ' ';
	// cout << endl;
	for (int i = 1; i <= n; i++) ans = max(ans, dis1[i]);
	// cerr << endl;
	print(ans, '\n');
	return;
}

int main() {
	read(n, s);
	for (int i = 1, u, v, w; i < n; i++) read(u, v, w), add(u, v, w), add(v, u, w);
	solve();
	return 0;
}