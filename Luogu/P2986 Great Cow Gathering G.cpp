#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 1e5 + 50;
const ll INF = 1e18;
int n, c[N], siz[N];
vector<Edge> e[N];
ll ans = INF, f[N], d[N], all;

inline void add(int u, int v , int w) {
	return (void)(e[u].emplace_back(v, w));
}

void dfs(int u, int from) {
	siz[u] = c[u];
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs(v, u), siz[u] += siz[v];
		f[u] += f[v] + (ll) siz[v] * w;
	}
	return;
}

void dfs2(int u, int from) {
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		d[v] = d[u] - (ll) siz[v] * w + (all - siz[v]) * w, ans = min(ans, d[v]), dfs2(v, u);
	}
	return;
}

void solve() {
	dfs(1, 0);
	ans = d[1] = f[1];
	dfs2(1, 0);
	cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> c[i], all += c[i];
	for (int i = 1, u, v, w; i < n; i++) 
		cin >> u >> v >> w, add(u, v, w), add(v, u, w);
	solve();
	return 0;
}