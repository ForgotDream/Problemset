#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 50, K = 25;
int n, k;
ll f[N][K], w[N], pivot;
vector<int> e[N];

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs1(int u, int from) {
	f[u][0] = w[u];
	for (auto v : e[u]) {
		if (v == from) continue;
		dfs1(v, u);
		for (int i = 1; i <= k; i++) f[u][i] += f[v][i - 1];
	}
	return;
}

void dfs2(int u, int from) {
	for (auto v : e[u]) {
		if (v == from) continue;
		for (int i = k; i >= 2; i--) f[v][i] += f[u][i - 1] - f[v][i - 2];
		f[v][1] += w[u];
		dfs2(v, u);
	}
	return;
}

void solve() {
	dfs1(1, 0);
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) {
		pivot = 0;
		for (int j = 0; j <= k; j++) pivot += f[i][j];
		cout << pivot << endl;
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for (int i = 1, u, v; i < n; i++) 
		cin >> u >> v, add(u, v), add(v, u);
	for (int i = 1; i <= n; i++) cin >> w[i];
	solve();
	return 0;
}