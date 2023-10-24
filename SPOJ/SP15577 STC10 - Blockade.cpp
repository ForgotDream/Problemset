#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define int long long

using namespace std;
using ll = long long;

const int N = 1e5 + 50;
int n, m;
int u, v;
int dfn[N], low[N], t, root;
bool cut[N];
ll ans[N];
int size[N];
vector<int> e[N];

void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++t, size[u] = 1;
	int child = 0;
	ll sum = 0;
	for (auto v : e[u]) {
		if (v == fa) continue;
		if (!dfn[v]) {
			tarjan(v, u);
			size[u] += size[v];
			low[u] = min(low[u], low[v]);
			// if (u == root && child > 1) cut[u] = true;
			if (low[v] >= dfn[u]) {
				child++, ans[u] += (ll)size[v] * (n - size[v]), sum += size[v];
				if (u != root || child > 1) cut[u] = true;
			}
		} else low[u] = min(low[u], dfn[v]);
	}
	if (cut[u]) ans[u] += (ll)(n - sum - 1) * (sum + 1) + (n - 1);
	else ans[u] = 2 * (n - 1);
	return;
}

void solve() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) root = i, tarjan(i, 0);
	for (int i = 1; i <= n; i++) cout << ans[i] << endl;
	return;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
	solve();
	return 0;
}