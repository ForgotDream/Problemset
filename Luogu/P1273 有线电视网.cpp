#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 3005, INF = 0x3f3f3f3f;
vector<Edge> e[N];
int n, m;
int f[N][N], siz[N];

inline void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w));
}

void dfs(int u) {
	siz[u] = 1;
	if (u >= n - m + 1 && u <= n) return;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		dfs(v), siz[u] += siz[v];
		for (int j = siz[u]; j >= 0; j--) 
			for (int k = 0; k <= siz[v]; k++)
				f[u][j] = max(f[u][j], f[u][j - k] + f[v][k] - w);
	}
	return;
}

void solve() {
	dfs(1);
	for (int i = m; i >= 1; i--)
		if (f[1][i] >= 0) return (void)(cout << i << endl);
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1, k, v, w; i <= n - m; i++) {
		cin >> k;
		while (k--) cin >> v >> w, add(i, v, w);
	}
	memset(f, -0x3f, sizeof f);
	for (int i = 1; i <= n; i++) f[i][0] = 0;
	for (int i = n - m + 1; i <= n; i++) cin >> f[i][1];
	solve();
	return 0;
}