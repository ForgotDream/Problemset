#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 20, INF = 0x3f3f3f3f;
int n, m;
int G[N][N], f[1 << N][N], dis[N][N], minn[1 << N], ans = INF;

inline void floydWarshall() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dis[i][j] = (i == j) ? 0 : G[i][j];
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
	// cerr << "OK" << endl;
	return;
}

void solve() {
	floydWarshall();
	memset(f, 0x3f, sizeof f), f[1][0] = 0;
	for (int i = 1; i < (1 << n); i++)
		for (int j = 0; j < n; j++)
			if (i & (1 << j))
				for (int k = 0; k < n; k++)
					if (!(i & (1 << k)))
						f[i | (1 << k)][k] = min(f[i | (1 << k)][k], f[i][j] + dis[j + 1][k + 1]);

	// cerr << "OK" << endl;

	memset(minn, 0x3f, sizeof minn);
	for (int i = 1; i < (1 << n); i++)
		for (int j = 0; j < n; j++) minn[i] = min(minn[i], f[i][j]);
	// for (int i = 1; i < (1 << n); i++) cout << minn[i] << endl;
	for (int i = 1; i < (1 << n); i++)
		for (int j = 0; j < n; j++)
			if (!(i & (1 << j)))
				minn[i] = min(minn[i], minn[i | (1 << j)]);

	for (int i = 1; i < (1 << n); i++)
		ans = min(ans, max(minn[i], minn[(1 << n) - 1 - i]));
	cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	memset(G, 0x3f, sizeof G);
	cin >> n >> m;
	for (int i = 1, u, v, w; i <= m; i++)
		cin >> u >> v >> w, G[u][v] = G[v][u] = w;
	solve();
	return 0;
}