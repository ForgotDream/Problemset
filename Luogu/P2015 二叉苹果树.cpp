#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 100 + 50, INF = 0x3f3f3f3f;
vector<Edge> e[N];
int n, m;
int f[N][N], siz[N], ch[N][2];

inline void add(int u, int v, int w) {
	return (void)(e[u].emplace_back(v, w));
}

void dfs(int u, int from) {
	siz[u] = 1;
	vector<int> wt(2, 0);
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == from) continue;
		if (!ch[u][0]) ch[u][0] = v, wt[0] = w;
		else ch[u][1] = v, wt[1] = w;
		dfs(v, u), siz[u] += siz[v];
	}
	if (!ch[u][1] && !ch[u][0]) return;
	else {
		for (int i = 1; i <= min(siz[u] - 1, m); i++) {
			int lc = ch[u][0], rc = ch[u][1];
			f[u][i] = max(f[lc][i - 1] + wt[0], f[rc][i - 1] + wt[1]);
			for (int j = 1; j <= i - 1; j++) {
				int tmp = wt[0] + f[lc][j - 1] + wt[1] + f[rc][i - j - 1];
				f[u][i] = max(f[u][i], tmp);
			}
		}
	}
	return;
}

void solve() {
	dfs(1, 0), cout << f[1][m] << endl;
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