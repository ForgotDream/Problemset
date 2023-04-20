#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 2e4 + 50;
int n, m;
int u, v;
vector<int> e[N];
int num, dfn[N], low[N], t, root;
bool cut[N];

void dfs(int u, int fa) {
	dfn[u] = low[u] = ++t;
	int child = 0;
	for (auto v : e[u]) {
		if (v == fa) continue;
		child++;
		if (!dfn[v]) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (u == root && child > 1) cut[u] = true;
			else if (u != root && low[v] >= dfn[u]) cut[u] = true;
		} else low[u] = min(low[u], dfn[v]);
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) root = i, dfs(i, 0);
	for (int i = 1; i <= n; i++) if (cut[i]) num++;
	cout << num << endl;
	for (int i = 1; i <= n; i++) if (cut[i]) cout << i << ' ';
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) 
		cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
	solve();
	return 0;
}