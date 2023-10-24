/**
 * @file    P7074 方格取数.cpp
 * @author  ForgotDream
 * @brief   DP + 记忆化搜索
 * @date    2023-02-13
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e3 + 50;
static const i64 INF = 1e18;
int n, m;
int a[N][N];
i64 f[N][N][2];
int d[][2] = {{1, 0}, {-1, 0}, {0, -1}};

i64 dfs(int x, int y, bool dwn) {
	if (y > m || y < 1 || x < 1 || x > n) return -INF;
	if (f[x][y][dwn] != -INF) return f[x][y][dwn];
	
	if (dwn) f[x][y][dwn] = max(max(dfs(x, y - 1, 0), dfs(x, y - 1, 1)), dfs(x + 1, y, 1));
	else f[x][y][dwn] = max(max(dfs(x, y - 1, 0), dfs(x, y - 1, 1)), dfs(x - 1, y, 0));

	f[x][y][dwn] += a[x][y];
	return f[x][y][dwn];
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j], f[i][j][0] = f[i][j][1] = -INF;

	f[1][1][0] = f[1][1][1] = a[1][1];

	cout << dfs(n, m, 0) << '\n';	
	return 0;
}