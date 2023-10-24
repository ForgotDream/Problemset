#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e6 + 50, INF = 0x3f3f3f3f;
int n;
vector<int> e[N];
int siz[N], dep[N], pivot;
ll f[N];

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs1(int u, int from) {
	siz[u] = 1, f[u] = dep[u] = dep[from] + 1;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs1(v, u), siz[u] += siz[v], f[u] += f[v];
	}
	return;
}

void dfs2(int u, int from) {
	for (int v : e[u]) {
		if (v == from) continue;
		f[v] = f[u] - (ll) 2 * siz[v] + n, dfs2(v, u);
	}
	return;
}

void solve() {
	dfs1(1, 0), dfs2(1, 0);
	for (int i = 1; i <= n; i++) if (f[pivot] < f[i]) pivot = i;
	cout << pivot << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1, u, v; i < n; i++) 
		cin >> u >> v, add(u, v), add(v, u);
	solve();
	return 0;
}