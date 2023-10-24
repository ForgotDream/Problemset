/**
 * @file    P4011 孤岛营救问题.cpp
 * @author  ForgotDream
 * @brief   BFS + 状压
 * @date    2023-02-10
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 15, INF = 0x3f3f3f3f;
int n, m, p, k, s;
struct Status {
	int x, y, st;
	Status() {}
	Status(int x, int y, int s) : x(x), y(y), st(s) {}
};
int bet[N][N][N][N];
int dis[N][N][1 << 10];
vector<int> key[N][N];
int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void bfs() {
	static queue<Status> q;
	int hst = 0;
	for (int v : key[1][1]) hst |= 1 << (v - 1);
	q.emplace(1, 1, hst);
	memset(dis, -1, sizeof(dis)), dis[1][1][hst] = 0;

	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		int curx = cur.x, cury = cur.y, st = cur.st;
		for (int i = 0; i < 4; i++) {
			int dx = curx + d[i][0], dy = cury + d[i][1];
			
			int tmp = bet[curx][cury][dx][dy];
			if (dx < 1 || dx > n || dy < 1 || dy > m) continue;
			// cerr << dx << ' ' << dy << '\n';
			if (!tmp || (tmp != -1 && !((1 << (tmp - 1)) & st))) continue;

			tmp = st;
			// if (key[dx][dy]) tmp |= 1 << (key[dx][dy] - 1);
			for (int v : key[dx][dy]) tmp |= 1 << (v - 1);
			
			// cerr << dx << ' ' << dy << ' ' << tmp << '\n';
			if (dis[dx][dy][tmp] != -1) continue;
			
			dis[dx][dy][tmp] = dis[curx][cury][st] + 1;
			// cerr << dx << ' ' << dy << ' ' << tmp << '\n';
			// if (dx == 4 && dy == 4) cerr << dis[dx][dy][tmp] << '\n';
			q.emplace(dx, dy, tmp);
		}
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	memset(bet, -1, sizeof bet);

	cin >> n >> m >> p >> k;
	for (int i = 1; i <= k; i++) {
		int x1, y1, x2, y2, type;
		cin >> x1 >> y1 >> x2 >> y2 >> type;
		bet[x1][y1][x2][y2] = type, bet[x2][y2][x1][y1] = type;
	}
	cin >> s;
	for (int i = 1, x, y, type; i <= s; i++) {
		cin >> x >> y >> type;
		key[x][y].push_back(type);
	}

	bfs();

	int ans = INF;
	for (int i = 0; i <= (1 << p); i++) if (~dis[n][m][i]) ans = min(ans, dis[n][m][i]);

	if (ans == INF) cout << -1 << '\n';
	else cout << ans << '\n';
	return 0;
}