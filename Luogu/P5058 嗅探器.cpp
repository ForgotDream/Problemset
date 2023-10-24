#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 2e5 + 50;
int n, m;
int u, v, st, ed;
vector<int> e[N], ans;
int low[N], dfn[N], t, root;

bool check(int u) {
	if (dfn[u] <= dfn[st] && dfn[u] > dfn[ed]) return true;
	if (dfn[u] <= dfn[ed] && dfn[u] > dfn[st]) return true;
	return false;
}

void tarjan(int u, int fa) {
	low[u] = dfn[u] = ++t;
	for (auto v : e[u]) {
		if (v == fa) continue;
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u] && u != st && u != ed && check(v)) ans.push_back(u);
		} else low[u] = min(low[u], dfn[v]);
	}
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, 0);
	if (ans.empty()) return (void)(cout << "No solution" << endl);
	sort(ans.begin(), ans.end());
	cout << ans[0] << endl;
	return;
}

int main() {
	cin >> n;
	while (cin >> u >> v) {
		if (!u && !v) break;
		e[u].push_back(v), e[v].push_back(u);
	}
	cin >> st >> ed;
	solve();
	return 0;
}