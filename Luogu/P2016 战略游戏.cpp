#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1.5e3 + 50;
int n;
vector<int> e[N];
int f[N][2];

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u, int from) {
	f[u][0] = 0, f[u][1] = 1;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u), f[u][1] += min(f[v][0], f[v][1]), f[u][0] += f[v][1];
	}
	return;
}

void solve() {
	dfs(1, 0);
	cout << min(f[1][0], f[1][1]) << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1, u, v, k; i <= n; i++) {
		cin >> u >> k;
		while (k--) cin >> v, add(u + 1, v + 1), add(v + 1, u + 1);
	}
	solve();
	return 0;
}