/**
 * @file    UVA11624 Fire!.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-02-21
 */
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e3 + 50, INF = 0x3f3f3f3f;
int T;
int n, m;
int minFireTime[N][N], dis[N][N];
bool cantReach[N][N];
int sx, sy;
int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

inline void init() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			minFireTime[i][j] = INF;
			cantReach[i][j] = false;
			dis[i][j] = 0;
		}
	}
	return;
}

void fireSpread() {
	queue<pair<int, int>> q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (minFireTime[i][j] == 0) {
				q.emplace(i, j);
			}
		}
	}

	while (!q.empty()) {
		auto u = q.front();
		q.pop();
		int curx = u.first, cury = u.second;
		for (int i = 0; i < 4; i++) {
			int dx = curx + d[i][0], dy = cury + d[i][1];
			if (dx < 1 || dx > n || dy < 1 || dy > m) {
				continue;
			} else if (cantReach[dx][dy]) {
				continue;
			}
			int tmp = minFireTime[curx][cury] + 1;
			if (minFireTime[dx][dy] != INF) {
				minFireTime[dx][dy] = min(minFireTime[dx][dy], tmp);
			} else {
				minFireTime[dx][dy] = tmp;
				q.emplace(dx, dy);
			}
		}
	}
	return;
}

int bfs() {
	queue<pair<int, int>> q;
	q.emplace(sx, sy);
	dis[sx][sy] = 0;
	if (sx == 1 || sx == n || sy == 1 || sy == m) {
		return 1;
	}

	while (!q.empty()) {
		auto u = q.front();
		q.pop();
		int curx = u.first, cury = u.second;
		for (int i = 0; i < 4; i++) {
			int dx = curx + d[i][0], dy = cury + d[i][1];
			if (dx < 1 || dx > n || dy < 1 || dy > m) {
				continue;
			} else if (cantReach[dx][dy]) {
				continue;
			} else if (dis[dx][dy] > 0 && (dx != sx || dy != sy)) {
				continue;
			} else if (dis[curx][cury] + 1 >= minFireTime[dx][dy]) {
				continue;
			}
			dis[dx][dy] = dis[curx][cury] + 1;
			if (dx == 1 || dx == n || dy == 1 || dy == m) {
				return dis[dx][dy] + 1;
			}
			q.emplace(dx, dy);
		}
	}

	return -1;
}

signed main() {
	ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

	cin >> T;
	while (T--) {
		cin >> n >> m;
		init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				char c;
				cin >> c;
				if (c == 'F') {
					minFireTime[i][j] = 0;
				} else if (c == 'J') {
					sx = i;
					sy = j;
				} else if (c == '#') {
					cantReach[i][j] = true;
				}
			}
		}

		fireSpread();
		int ans = bfs();
		if (~ans) {
			cout << ans << '\n';
		} else {
			cout << "IMPOSSIBLE" << '\n';
		}
	}

	return 0;
}