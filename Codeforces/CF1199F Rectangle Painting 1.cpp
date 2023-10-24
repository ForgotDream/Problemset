// 二维区间 DP
// 时间复杂度 O(n ^ 5)

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 55, M = 20, INF = 0x3f3f3f3f;
int n;
char mat[N][N];
int sum[N][N], f[N][N][N][N];

void solve() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (mat[i][j] == '#');
	for (int i = 1; i <= n; i++)
		for (int j = 1; j + i - 1 <= n; j++)
			for (int k = 1; k <= n; k++)
				for (int l = 1; l + k - 1 <= n; l++) {
					int m = j + i - 1, n = l + k - 1;
					if (sum[m][n] - sum[m][n - k] - sum[m - i][n] + sum[m - i][n - k]) f[j][l][m][n] = max(i, k);
					for (int p = j; p < m; p++) f[j][l][m][n] = min(f[j][l][m][n], f[j][l][p][n] + f[p + 1][l][m][n]);
					for (int p = l; p < n; p++) f[j][l][m][n] = min(f[j][l][m][n], f[j][l][m][p] + f[j][p + 1][m][n]);
				}
	cout << f[1][1][n][n] << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++)
			cin >> mat[i][j];
	solve();
	return 0;
}