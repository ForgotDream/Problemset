#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e5 + 50;
int n, m;
vector<int> e[N];
vector<int> color(N, -1);
bool vis[N];
int ans, cur;

void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs(int u, int c = 0) {
	color[u] = c, cur++, vis[u] = true;
	for (auto v : e[u])
		if (color[v] == -1) dfs(v, c ^ 1);
		else if (color[v] == c) cout << "Impossible" << endl, exit(0);
	return;
}

void solve() {
	// for (int i = 1; i <= n; i++) cout << color[i] << endl;
	for (int i = 1, t = 0; i <= n; i++)
		if (!vis[i]) {
			fill(color.begin() + 1, color.begin() + n + 1, -1);
			dfs(i);
			for (int i = 1; i <= n; i++) t += color[i] == 1;
			ans += min(t, cur - t), t = 0, cur = 0;
		}
	cout << ans << endl;
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++) cin >> u >> v, add(u, v), add(v, u);
	solve();
	return 0;
}