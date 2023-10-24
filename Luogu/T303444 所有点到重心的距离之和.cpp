#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using Edge = pair<int, int>;
using ll = long long;

const int N = 2e5 + 50;
int n, pivot;
vector<Edge> e[N];
int siz[N], maxNum[N], cnt;
ll dis[N];

inline void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w));
}

void dfs1(int u, int from) {
	siz[u] = 1;
	for (auto i : e[u]) {
		int v = i.first;
		if (v == from) continue;
		dfs1(v, u), siz[u] += siz[v], maxNum[u] = max(maxNum[u], siz[v]);
	}
	maxNum[u] = max(maxNum[u], n - siz[u]);
	if (maxNum[u] <= (n >> 1)) pivot = u;
	return;
}

void dfs2(int u, int from) {
	siz[u] = 1;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs2(v, u), siz[u] += siz[v], dis[u] += dis[v] + (ll)w * siz[v];
	}
	return;
}

void solve() {
	dfs1(1, 0);
	dfs2(pivot, 0);
	cout << pivot << ' ' << dis[pivot] << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1, u, v, w; i < n; i++) 
		cin >> u >> v >> w, add(u, v, w), add(v, u, w);
	solve();
	return 0;
}