#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using Edge = pair<int, int>;

const int N = 5050, M = 1e4 + 50;
int n, m;
int u[N], v[N];
vector<Edge> e[N];
int dfn[N], low[N], t;
bool bridge[2 * M];
int belong[N], cnt, deg[2 * M], ans;

void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++t;
	for (auto i : e[u]) {
		int v = i.first, no = i.second;
		if (v == fa) continue;
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (dfn[u] < low[v]) bridge[no] = bridge[no ^ 1] = true;
		} else low[u] = min(low[u], dfn[v]);
	}
	return;
}

void dfs(int u) {
	belong[u] = cnt;
	for (auto i : e[u]) {
		int v = i.first, no = i.second;
		if (belong[v] || bridge[no]) continue;
		dfs(v);
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, 0);
	for (int i = 1; i <= n; i++) if (!belong[i]) ++cnt, dfs(i);
	for (int i = 1; i <= m; i++) 
		if (belong[u[i]] != belong[v[i]]) deg[belong[u[i]]]++, deg[belong[v[i]]]++;
	for (int i = 1; i <= cnt; i++) if (deg[i] == 1) ans++;
	return (void)(cout << ((ans + 1) / 2) << endl);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) 
		cin >> u[i] >> v[i], e[u[i]].emplace_back(v[i], 2 * i), e[v[i]].emplace_back(u[i], 2 * i + 1);
	solve();
	return 0;
}