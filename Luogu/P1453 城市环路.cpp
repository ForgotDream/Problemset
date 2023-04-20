#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 50;
vector<int> e[N];
int n;
bool vis[N], flg;
int s, t;
double val[N], k, f[N][2], ans;

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void findCircle(int u, int from) {
	if (flg) return;
	vis[u] = true;
	for (int v : e[u]) {
		if (v == from) continue;
		if (vis[v]) return (void)(s = u, t = v);
		findCircle(v, u);
	}
	return;
}

void dfs(int u, int from) {
	f[u][0] = 0, f[u][1] = val[u];
	for (int v : e[u]) {
		if (v == from || (u == s && v == t) || (u == t && v == s)) continue;
		dfs(v, u);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> val[i];
	for (int i = 1, u, v; i <= n; i++) 
		cin >> u >> v, u++, v++, add(u, v), add(v, u);
	cin >> k;

	findCircle(1, 0);
	memset(vis, 0, sizeof vis);
	vis[s] = vis[t] = true;

	// for (int i = 1; i <= n; i++) if (!vis[i]) calc(i);
	dfs(s, 0), ans = f[s][0];
	memset(f, 0, sizeof f);
	dfs(t, 0), ans = max(ans, f[t][0]);
	cout << fixed << setprecision(1) << (double) ans * k << endl;
	return 0;
}