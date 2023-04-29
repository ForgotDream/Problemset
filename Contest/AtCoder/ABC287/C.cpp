#include <bits/stdc++.h>
#include <type_traits>

using namespace std;

const int N = 2e5 + 50;
int n, m;
vector<int> e[N];
bool vis[N], flag = true;
int clk, link[N];

inline void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

bool dfs(int u, int from) {
	vis[u] = true, link[++clk] = u;
	for (int v : e[u]) {
		if (v == from) continue;
		if (vis[v]) {
			flag = false;
			continue;
		}
		dfs(v, u); 
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v, add(u, v), add(v, u);
	}

	dfs(1, 0);
	if (clk != n || !flag) cout << "No" << endl;
	else cout << "Yes" << endl;
	return 0;
}