/**
 * @file    P1514 引水入城.cpp
 * @author  ForgotDream
 * @brief   记忆化搜索
 * @date    2023-02-17
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 550, INF = 0x3f3f3f3f;
int n, m, cnt, len;
bool vis[N][N], used[N];
int a[N][N], rst, t[N][N];
int l[N][N], r[N][N];
int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void dfs(int sx, int sy) {
	vis[sx][sy] = true, t[sx][sy]++;
	// cerr << sx << ' ' << sy << '\n';
	for (int i = 0; i < 4; i++) {
		int dx = sx + d[i][0], dy = sy + d[i][1];
		if (dx < 1 || dx > n || dy < 1 || dy > m
		 || vis[dx][dy] || a[dx][dy] >= a[sx][sy]) continue;
		dfs(dx, dy);
		l[sx][sy] = min(l[sx][sy], l[dx][dy]);
		r[sx][sy] = max(r[sx][sy], r[dx][dy]);
	}
	return;
}

void init() {
	memset(l, 0x3f, sizeof(l));
	for (int i = 1; i <= m; i++) l[n][i] = r[n][i] = i;
	return;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) cin >> a[i][j];

	init();

	for (int i = 1; i <= m; i++) memset(vis, 0, sizeof(vis)), dfs(1, i);

	for (int i = 1; i <= m; i++) 
		if (!t[n][i]) rst++;

	if (rst) return cout << 0 << '\n' << rst << '\n', 0;
	cout << 1 << '\n';

	int pivot = 1;
	while (pivot <= m) {
		len = 0;
		for (int i = 1; i <= m; i++)
			if (l[1][i] <= pivot) len = max(len, r[1][i]);
		cnt++, pivot = len + 1;
	}

	cout << cnt << '\n';
	return 0;
}