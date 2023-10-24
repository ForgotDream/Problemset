#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 305, INF = 0x3f3f3f3f;
int n, p;
vector<int> e[N];
int w[N], f[N][N], ans = INF, siz[N];

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u) {
	f[u][1] = e[u].size(), siz[u] = 1;
	for (int v : e[u]) {
		dfs(v), siz[u] += siz[v];
		for (int i = min(siz[u], p); i >= 0; i--)
			for (int j = 1; j < i; j++)
				f[u][i] = min(f[u][i], f[u][i - j] + f[v][j] - 1);
	}
	ans = min(ans, f[u][p] + (u != 1));
	return;
}

void solve() {
	memset(f, 0x3f, sizeof f), dfs(1);
	cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> p;
	for (int i = 1, u, v; i < n; i++) cin >> u >> v, add(u, v);
	solve();
	return 0;
}