#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

const int N = 2e3 + 50;
int T, n, m;
int c[N];
vector<int> e[N];
int dis[N][N];

inline void init() {
	memset(dis, -1, sizeof(dis));
	for (int i = 1; i <= n; i++) e[i].clear();
	return;
}

inline void add(int u, int v) {
	return (void) (e[u].push_back(v));
}

int bfs() {
	queue<pair<int, int>> q;
	q.emplace(1, n), dis[1][n] = 0;

	while (!q.empty()) {
		auto u = q.front();
		int curx = u.first, cury = u.second;
		for (auto i : e[curx]) 
			for (auto j : e[cury]) 
				if (dis[i][j] == -1 && c[i] != c[j]) {
					// cerr << n << ' ' << i << ' ' << j << '\n' 
					//	 << "  " << curx << ' ' << cury << '\n';
					dis[i][j] = dis[curx][cury] + 1;
					if (i == n && j == 1) return dis[i][j];
					q.emplace(i, j);
				}
		q.pop();
	}

	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> T;
	while (T--) {
		init();
		cin >> n >> m;
		// cerr << n << ' ' << m << '\n';
		for (int i = 1; i <= n; i++) cin >> c[i];
		for (int i = 1, u, v; i <= m; i++) 
			cin >> u >> v, add(u, v), add(v, u);
		if (c[1] == c[n]) cout << -1 << '\n';
		else cout << bfs() << '\n';
	}

	return 0;
}