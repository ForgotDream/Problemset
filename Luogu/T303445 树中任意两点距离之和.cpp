#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 2e5 + 50;
int n, siz[N];
ll f[N], d[N];
vector<Edge> e[N];

void dfs(int u, int from) {
	siz[u] = 1;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs(v, u);
		d[u] += d[v] + f[u] * siz[v] + f[v] * siz[u] + (ll) siz[u] * siz[v] * w;
		f[u] += f[v] + (ll) siz[v] * w;
		siz[u] += siz[v];
	}
	return;
}

inline void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1, u, v, w; i < n; i++) 
		cin >> u >> v >> w, add(u, v, w), add(v, u, w);
	dfs(1, 0);
	cout << d[1] << endl;
	return 0;
}