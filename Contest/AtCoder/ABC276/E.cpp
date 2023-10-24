#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int h, w;
int sx, sy;
char m[1050][1050];
bool vis[1050][1050];
int d[][2] = {{0, 1}, {0, -1}, {1, 0}, { -1, 0}};

void dfs(int x = sx, int y = sy, int cnt = 0, bool first = true) {
	if (m[x][y] == 'S' && first == false) {
		// cout << cnt << endl;
		if (cnt >= 4) {
			cout << "Yes" << endl;
			exit(0);
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		int dx = x + d[i][0], dy = y + d[i][1];
		if (!vis[dx][dy] && (m[dx][dy] == '.' || m[dx][dy] == 'S')) {
			vis[dx][dy] = true;
			// cout << dx << ' ' << dy << endl;
			dfs(dx, dy, cnt + 1, false);
			vis[dx][dy] = false;
		}
	}
	return;
}

void solve() {
	// vis[sx][sy] = true;
	dfs();
	cout << "No" << endl;
	return;
}

int main() {
	cin >> h >> w;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> m[i][j];
			if (m[i][j] == 'S') sx = i, sy = j;
		}
	}
	solve();
	return 0;
}