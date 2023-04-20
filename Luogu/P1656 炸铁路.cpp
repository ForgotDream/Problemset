#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 200;
int n, m;
int u, v;
vector<int> e[N];
int num, dfn[N], low[N], t;
bool cut[N][N];

void dfs(int u, int fa) {
	dfn[u] = low[u] = ++t;
	for (auto v : e[u]) {
		if (v == fa) continue;
		if (!dfn[v]) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) cut[u][v] = true, cut[v][u] = true, num++;
		} else low[u] = min(low[u], dfn[v]);
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i, 0);
	for (int i = 1; i <= n; i++) 
		for (int j = i + 1; j <= n; j++)
			if (cut[i][j]) cout << i << ' ' << j << endl;
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) 
		cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
	solve();
	return 0;
}