#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;

const int N = 2e5 + 50;
int n, m, cnt, color[N], belong[N];
vector<int> e[N];
int dfn[N], tclock, ans, all;

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

bool dfs(int u, int from) {
	dfn[u] = ++tclock;
	if (~color[u] && color[u] == color[from]) return false;
	else if (~color[u]) return true;
	else color[u] = 1 ^ color[from], all += color[u];
	for (int v : e[u]) {
		if (v == from) continue;
		if (!dfs(v, u)) return false;
	}
	return true;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) if (!dfs(i, 0)) return (void)(cout << 0 << endl);
	for (int i = 1; i <= n; i++) if (!color[i]) ans += all - e[i].size();
	cout << ans << endl;
	return;
}

int main() {
	cin >> n >> m;
	fill(color + 1, color + n + 1, -1);
	for (int i = 1, u, v; i <= m; i++) cin >> u >> v, add(u, v), add(v, u);
	solve();
	return 0;
}

// 加边后变成二分图？
// 什么阴间玩意