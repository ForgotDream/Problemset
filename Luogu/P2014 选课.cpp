#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 305, INF = 0x3f3f3f3f;
int n, m;
vector<int> e[N];
int w[N], f[N][N];

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u) {
	f[u][1] = w[u];
	for (int v : e[u]) {
		dfs(v);
		for (int i = m + 1; i >= 1; i--)
			for (int j = i - 1; j >= 0; j--)
				f[u][i] = max(f[u][i], f[u][i - j] + f[v][j]);
	}
	return;
}

void solve() {
	dfs(0);
	cout << f[0][m + 1] << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1, f; i <= n; i++) cin >> f >> w[i], add(f, i);
	solve();
	return 0;
}