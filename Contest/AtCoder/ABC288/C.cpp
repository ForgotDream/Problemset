#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 50;
int n, m, ans;
vector<int> e[N];
int clk, dfn[N], low[N], cnt;
stack<int> st;
bool flag;

inline void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

void dfs(int u, int from) {
	dfn[u] = low[u] = ++clk;
	for (int v : e[u]) {
		if (v == from) continue;
		if (!dfn[v]) {
			dfs(v, u), low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) cnt++;
		}
		else low[u] = min(low[u], dfn[v]), flag = true;
	}
	if (dfn[u] == low[u]) cnt++;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++) 
		cin >> u >> v, add(u, v), add(v, u);

	for (int i = 1; i <= n; i++) if (!dfn[i]) cnt = 0, flag = false, dfs(i, 0), ans += cnt * flag;
	// for (int i = 1; i <= n; i++) cerr << dfn[i] << ' ' << low[i] << '\n';
	
	cout << ans << '\n';
 	return 0;
}