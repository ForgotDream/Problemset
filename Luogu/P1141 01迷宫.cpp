/**
 * @file    P1141 01迷宫.cpp
 * @author  ForgotDream
 * @brief   BFS + 一点小小的离线思想
 * @date    2023-02-10
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 1e3 + 50;
int n, mat[N][N], ans[N][N], m;
bool vis[N][N];
int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void bfs(int sx, int sy) {
	static queue<pair<int, int>> q;
	static stack<pair<int, int>> s;
	q.emplace(sx, sy), s.emplace(sx, sy);
	vis[sx][sy] = true;
	int res = 1;

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int dx = cur.first + d[i][0], dy = cur.second + d[i][1];
			if (dx < 1 || dx > n || dy < 1 || dy > n || vis[dx][dy]) continue;
			if (mat[cur.first][cur.second] == mat[dx][dy]) continue;
			q.emplace(dx, dy), s.emplace(dx, dy);
			res++, vis[dx][dy] = true;
 		}
	}

	while (!s.empty()) {
		int curx = s.top().first, cury = s.top().second;
		s.pop();
		ans[curx][cury] = res;
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			char ch;
			cin >> ch, mat[i][j] = ch - '0';
		}

	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++)
			if (!vis[i][j]) bfs(i, j);

	while (m--) {
		int x, y;
		cin >> x >> y, cout << ans[x][y] << '\n';
	}
	return 0;
}