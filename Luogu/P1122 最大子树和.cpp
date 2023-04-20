#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1.6e4 + 50, INF = 0x3f3f3f3f;
vector<int> e[N];
int n, w[N], f[N], ans = -2 * INF;

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u, int from) {
	f[u] = w[u];
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u), f[u] += (f[v] > 0) * f[v];
	}
	ans = max(ans, f[u]);
	return;
}

void solve() {
	dfs(1, 0), cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> w[i];
	for (int i = 1, u, v; i < n; i++) 
		cin >> u >> v, add(u, v), add(v, u);
	solve();
	return 0;
}