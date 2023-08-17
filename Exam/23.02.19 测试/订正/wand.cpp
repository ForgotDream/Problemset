#include <iostream>

using namespace std;
using i64 = long long;

static const int N = 1e3 + 50;
int n, lo, hi;
int l[N], m[N], ans;
i64 f[N][N], sum[N][2];

void dfs(int cur) {
	return;
}

int main() {
	// freopen("wand.in", "r", stdin);
	// freopen("wand.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> lo >> hi;
	for (int i = 1; i <= n; i++) {
		cin >> l[i];
		sum[i][0] = sum[i - 1][0] + l[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> m[i];
		sum[i][1] = sum[i - 1][1] + m[i];
	}
	
	/*
	for (int i = 1; i <= n; i++) {
		cerr << sum[i][0] << ' ' << sum[i][1] << '\n';
	}
	*/
	
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			int tmp = sum[j][0] - sum[i - 1][0];
			f[i][j] = max(f[i - 1][j], f[i][j - 1]);
			if (tmp >= lo && tmp <= hi) {
				f[i][j] = max(f[i][j], f[i - 1][j - 1] + sum[j][1] - sum[i - 1][1]);
			}
			// cerr << i << ' ' << j << ' ' << f[i][j] << '\n';
		}
	}
	
	cout << f[n][n] << '\n';
	
	return 0;
}
