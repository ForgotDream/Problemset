#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 5e5 + 50;
int n;
vector<int> e[N];
int f[N][2];

void dfs(int u, int from) {
	f[u][0] = 0, f[u][1] = 1;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs(v, u), f[u][0] += max(f[v][0], f[v][1]), f[u][1] += f[v][0];
	}
	return;
}

void solve() {
	dfs(1, 0);
	cout << max(f[1][1], f[1][0]) << endl;
	return;
}

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1, u, v; i < n; i++)
		cin >> u >> v, add(u, v), add(v, u);
	solve();
	return 0;
}