#include <iostream>

using namespace std;
using ll = long long;

const int N = 550, MOD = 1e9 + 7;
int n, m;
char a[N][N];
int f[N][N], g[N][N];
int d[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
int ans;

void solve() {
	f[1][m] = (a[1][1] == a[n][m]);
	int t = 1;
	for (t = 1; t < ((n + m) >> 1); t++) {
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++)
				g[i][j] = f[i][j], f[i][j] = 0;
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++)
				if (g[i][j]) {
					int x1 = t - i + 1, y1 = i;
					int x2 = n - (t - (m - j) - 1), y2 = j;
					for (int k1 = 0; k1 < 2; k1++)
						for (int k2 = 2; k2 < 4; k2++) {
							int dx1 = x1 + d[k1][0], dx2 = x2 + d[k2][0];
							int dy1 = y1 + d[k1][1], dy2 = y2 + d[k2][1];
							if (dx1 <= n && dx2 >= 1 && dy1 <= m && dy2 >= 1 && a[dx1][dy1] == a[dx2][dy2]) 
								f[dy1][dy2] = (f[dy1][dy2] + g[i][j]) % MOD;
						}
				}
	}
	// cerr << t << endl;
	if ((n + m - 1) & 1) for (int i = 1; i <= m; i++) ans = (ans + f[i][i]) % MOD;
	else for (int i = 1; i <= m; i++) ans = (ans + f[i][i]) % MOD, ans = (ans + f[i][i + 1]) % MOD;
	cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> (a[i] + 1);
	solve();
	return 0;
}