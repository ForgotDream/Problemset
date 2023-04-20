#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 250, INF = 0x3f3f3f3f;
int n, m, q;
int gr[N][N], time_[N];
int u, v, cur = 1;
int x, y, t;

void update(int u) {
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++)
			gr[i][j] = min(gr[i][j], gr[i][u] + gr[u][j]);
	return;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> time_[i];
	memset(gr, 0x3f, sizeof gr);
	for (int i = 1; i <= m; i++) 
		cin >> u >> v >> gr[u + 1][v + 1], gr[v + 1][u + 1] = gr[u + 1][v + 1];
	for (int i = 1; i <= n; i++) gr[i][i]= 0;
	cin >> q;
	while (q--) {
		cin >> x >> y >> t;
		x++, y++;
		while (time_[cur] <= t && cur <= n) update(cur), cur++;
		if (time_[x] > t || time_[y] > t || gr[x][y] == INF) {
			cout << -1 << endl;
			continue;
		}
		cout << gr[x][y] << endl;
	}
	return 0;
}