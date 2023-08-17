#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using i64 = long long;

static const int N = 55, INF = 0x3f3f3f3f;
int n, m, k1, k2, ans = INF;
int a[N][N], d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
pair<int, int> mp[N];

void solve(int x, int y, int cur) {
	a[x][y] = cur; 
	mp[cur].first = x;
	mp[cur].second = y;
	if (cur == n * m) {
		int tmp = -INF;
		for (int i = 1; i <= n * m / 2; i++) {
			int x1 = mp[i].first, y1 = mp[i].second;
			int x2 = mp[i + n * m / 2].first, y2 = mp[i + n * m / 2].second;
			
			tmp = max(tmp, k1 * abs(x1 - x2) + k2 * abs(y1 - y2));
		}
		a[x][y] = -1;
		ans = min(ans, tmp);
		return;
	}
	
	for (int i = 0; i < 4; i++) {
		int dx = x + d[i][0], dy = y + d[i][1];
		if (~a[dx][dy]) continue;
		if (dx < 1 || dx > n || dy < 1 || dy > m) continue;
		solve(dx, dy, cur + 1);
	}
	
	a[x][y] = -1;
	return;
}

int main() {
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m >> k1 >> k2;
	
	memset(a, -1, sizeof(a));
	solve(1, m, 1);
	
	cout << ans << '\n';
	return 0;
}
