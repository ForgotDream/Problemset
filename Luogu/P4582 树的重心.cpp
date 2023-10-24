// 麻烦，鸽了

#include <bits/stdc++.h>

using namespace std;

const int N = 205, MOD = 1e4 + 7, INF = 0x3f3f3f3f;
int T, n;
vector<int> e[N];
int siz[N], maxNum[N], CG[2], f[N][N];

inline void init() {
	fill(maxNum + 1, maxNum + n + 1, 0);
	maxNum[0] = INF, CG[0] = CG[1] = 0;
	for (int i = 1; i <= n; i++) e[i].clear();
	return;
}

inline void add(int u, int v) {
	return (void)(e[u].push_back(v));
}

void dfs1(int u, int from) {
	siz[u] = 1;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs1(v, u); 
		siz[u] += siz[v], maxNum[u] = max(maxNum[u], siz[v]);
	}
	maxNum[u] = max(maxNum[u], n - siz[u]);
	if (maxNum[CG[0]] > maxNum[u]) CG[0] = u, CG[1] = 0;
	else if (maxNum[CG[0]] == maxNum[u]) CG[1] = u;
	return;
}

void dfs2(int u, int from) {
	f[u][0] = f[u][1] = siz[u] = 1;
	for (int v : e[u]) {
		if (v == from) continue;
		dfs2(v, u), siz[u] += siz[v];
		for (int i = siz[u]; i >= 0; i--) 
			for (int j = 1; j <= min(i - 1, siz[u]); j++)
				f[u][i] = (f[u][i] + f[v][j] * f[u][i - j]) % MOD;
	}
	return;
}

void solve() {
	dfs1(1, 0);
	if (!CG[1]) {

	} else {

	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		cin >> n;
		for (int i = 1, u, v; i < n; i++) 
			cin >> u >> v, add(u, v), add(v, u);
		solve();
	}
	return 0;
}