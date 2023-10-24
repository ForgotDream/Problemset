#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
using ll = long long;
using Edge = pair<int, ll>;

const int N = 2e5 + 50;
int n;
vector<Edge> e[N];
ll dis1[N], dis2[N];
int pre[N], suc[N];
bool vis[N];
int L, R, tmp;
ll maxDis[N], maxx;
int ans;

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

void dfs1(int u, int from, int d) {
	vis[u] = true, dis1[u] = dis1[from] + d;
	if (dis1[u] > maxx) maxx = dis1[u], tmp = u;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (vis[v] || v == from) continue;
		dfs1(v, u, w);
	}
	return;
}

void dfs2(int u, int from , int d) {
	pre[u] = from, dis2[u] = dis2[from] + d;
	if (dis2[u] > maxx) maxx = dis2[u], tmp = u;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs2(v, u, w);
	}
	return;
}

void solve() {
	dfs1(1, 0, 0), maxx = 0, L = tmp;
	dfs2(L, 0, 0), R = tmp;
	// cerr << L << ' ' << R << endl;

	print(maxx, '\n');

	memset(vis, 0, sizeof vis);
	for (int i = R; i; i = pre[i]) vis[i] = true;
	for (int i = R; i; i = pre[i]) maxx = 0, dfs1(i, 0, 0), maxDis[i] = maxx;

	int pivot = R;
	for (int i = pre[R]; i; i = pre[i]) suc[i] = pivot, pivot = i;
	int k = pivot;
	for (k = pivot; k; k = suc[k]) if (dis2[R] - dis2[k] == maxDis[k]) break;
	for (k; k; k = pre[k]) {
		if (dis2[k] == maxDis[k]) break;
		ans++;
	}
	// for (int i = 1;i <= n; i++) cerr << maxDis[i] << ' ';
	// cerr << endl;
	print(ans, '\n');
	return;
}

int main() {
	read(n);
	for (int i = 1, u, v, w; i < n; i++) read(u, v, w), addEdge(u, v, w), addEdge(v, u, w);
	solve();
	return 0;
}