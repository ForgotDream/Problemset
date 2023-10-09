#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e4 + 50;
int t, n, ans;
vector<int> e[N];
int maxNum[N], siz[N];

inline void init() {
	for (int i = 1; i <= n; i++) e[i].clear();
	fill(maxNum + 1, maxNum + n + 1, 0), fill(siz + 1, siz + n + 1, 0);
	return;
}

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u, int from) {
	siz[u] = 1;
	for (int i = 0; i < e[u].size(); i++) {
		int v = e[u][i];
		if (v == from) continue;
		dfs(v, u), siz[u] += siz[v], maxNum[u] = max(maxNum[u], siz[v]);
	}
	maxNum[u] = max(maxNum[u], n - siz[u]);
	if (maxNum[u] < maxNum[ans]) ans = u;
	else if (maxNum[u] == maxNum[ans] && ans > u) ans = u;
	return;
}

void solve() {
	maxNum[ans] = 0x3f3f3f3f;
	dfs(1, 0);
	cout << ans << ' ' << maxNum[ans] << endl;
	return;
}

int main() {
	cin >> t;
	while (t--) {
		init();
		cin >> n;
		for (int i = 1, u, v; i < n; i++) cin >> u >> v, add(u, v), add(v, u);
		solve();
	}
	return 0;
}
