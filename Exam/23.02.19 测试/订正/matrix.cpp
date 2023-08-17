#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using i64 = long long;

static const int N = 55, INF = 0x3f3f3f3f;
int n, m, k1, k2, ans = INF;
int a[N][N], d[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
pair<int, int> mp[N];

bool check(int x, int y) {
	if (a[x - 1][y] && a[x + 1][y] && !a[x][y - 1] && !a[x][y + 1]) {
		return false;
	} else if (!a[x - 1][y] && !a[x + 1][y] && a[x][y - 1] && a[x][y + 1]) {
		return false;
	} else {
		return true;
	}
}

void solve(int x, int y, int cur, int t = -INF) {
	a[x][y] = cur; 
	mp[cur].first = x;
	mp[cur].second = y;
	if (cur == n * m) {
		ans = min(ans, t);
		a[x][y] = 0;
		return;
	} 
	if (!check(x, y)) {
		// cout << "True" << '\n';
		a[x][y] = 0;
		return;
	} 
	if (cur > n * m / 2) {
		int x1 = mp[cur].first, y1 = mp[cur].second;
		int x2 = mp[cur - n * m / 2].first, y2 = mp[cur - n * m / 2].second;
		t = max(t, k1 * abs(x1 - x2) + k2 * abs(y1 - y2));
		if (t > ans) {
			a[x][y] = 0;
			return;
		}
	} 
	
	for (int i = 0; i < 4; i++) {
		int dx = x + d[i][0], dy = y + d[i][1];
		if (a[dx][dy]) continue;
		if (dx < 1 || dx > n || dy < 1 || dy > m) continue;
		solve(dx, dy, cur + 1, t);
	}
	
	a[x][y] = 0;
	return;
}

int main() {
	// freopen("matrix.in", "r", stdin);
	// freopen("matrix.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m >> k1 >> k2;

	// memset(a, -1, sizeof(a));
	for (int i = 0; i <= n + 1; i++) {
		a[i][0] = 1;
		a[i][m + 1] = 1;
	}
	for (int i = 0; i <= m + 1; i++) {
		a[0][i] = 1;
		a[n + 1][i] = 1;
	}
	solve(1, 1, 1);
	
	cout << ans << '\n';
	return 0;
}
