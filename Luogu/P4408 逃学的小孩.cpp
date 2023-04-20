#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;
using Edge = pair<int, ll>;

const int N = 2e5 + 50;
int n, m;
vector<Edge> e[N];
ll dis1[N], dis2[N], maxx;
int A, B;

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

inline void addEdge(int u, int v, ll w) {
	return (void)(e[u].emplace_back(v, w));
}

void dfs1(int u, int from, int weigh) {
	dis1[u] = dis1[from] + weigh;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs1(v, u, w);
	}
	return;
}

void dfs2(int u, int from, int weigh) {
	dis2[u] = dis2[from] + weigh;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs2(v, u, w);
	}
	return;
}

void solve() {
	dfs1(1, 0, 0);
	for (int i = 1; i <= n; i++) if (dis1[i] > maxx) maxx = dis1[i], A = i;
	dfs1(A, 0, 0), maxx = 0;
	// cerr << A << endl;
	for (int i = 1; i <= n; i++) if (dis1[i] > maxx) maxx = dis1[i], B = i;
	// cerr << B << endl;
	dfs2(B, 0, 0), maxx = 0;
	for (int i = 1; i <= n; i++) maxx = max(maxx, dis1[B] + min(dis1[i], dis2[i]));
	print(maxx, '\n');
	return;
}

int main() {
	read(n, m);
	for (int i = 1, u, v, w; i <= m; i++) read(u, v, w), addEdge(u, v, w), addEdge(v, u, w);
	solve();
	return 0;
}