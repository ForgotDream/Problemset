#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 2005, INF = 0x3f3f3f3f;
vector<Edge> e[N];
int n, m, siz[N];
ll f[N][N];

inline void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w));
}

void dfs(int u, int from) {
	siz[u] = 1, f[u][0] = f[u][1] = 0;   // j == 0 || j == 1 is always legal
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		dfs(v, u), siz[u] += siz[v];
		for (int j = min(m, siz[u]); ~j; j--) 
			for (int k = 0; k <= min(j, siz[v]); k++) {
				if (!(~f[u][j - k])) continue;
				ll tmp = (ll) w * k * (m - k) + (ll) w * (siz[v] - k) * (n - m - siz[v] + k);
				f[u][j] = max(f[u][j], f[u][j - k] + f[v][k] + tmp);
			}
	}
	return;
}

void solve() {
	memset(f, -1, sizeof f), dfs(1, 0);   // -1 means illegal
	cout << f[1][m] << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1, u, v, w; i < n; i++)
		cin >> u >> v >> w, add(u, v, w), add(v, u, w);
	solve();
	return 0;
}