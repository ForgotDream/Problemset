#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e4 + 50, INF = 0x3f3f3f3f;
int m, n, c[N];
vector<int> e[N];
int f[N][2];

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u, int from) {
	if (u <= n) return;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u); 
		f[u][0] += min(f[v][0] - 1, f[v][1]), f[u][1] += min(f[v][1] - 1, f[v][0]);
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) f[i][c[i]] = 1, f[i][!c[i]] = INF;
	for (int i = n + 1; i <= m; i++) f[i][0] = f[i][1] = 1;
	dfs(n + 1, 0);
	cout << min(f[n + 1][0], f[n + 1][1]) << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> m >> n;
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1, u, v; i < m; i++) 
		cin >> u >> v, add(u, v), add(v, u);
	solve();
	return 0;
}