#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
using Edge = pair<int, int>;

const int N = 105, INF = 0x1f1f1f1f;
int n, m, ans = INF;
int g[N][N], dis[N][N];

int main() {
	cin >> n >> m;
	memset(g, 0x1f, sizeof g);
	for (int i = 1, u, v, w; i <= m; i++) cin >> u >> v >> w, g[u][v] = g[v][u] = w;
	for (int i = 1; i <= n; i++) g[i][i] = 0;
	memcpy(dis, g, sizeof dis);
	// cout << g[2][1] << endl;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i < k; i++) 
			for (int j = 1; j < i; j++) 
				ans = min(dis[i][j] + g[i][k] + g[k][j], ans);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
	}
	ans == INF ? (cout << "No solution." << endl) : (cout << ans << endl);
	return 0;
}
