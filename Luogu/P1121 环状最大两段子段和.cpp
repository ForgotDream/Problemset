/**
 * @file    P1121 环状最大两段子段和.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-02-12
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 2e5 + 50;
int n, a[N];
int f[N][2], g[N][2];
int maxx[N][2], minn[N][2];
int sum, mx = -1e5, mi = 1e5, t;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i], sum += a[i], mx = max(mx, a[i]);
	}

	if (mx < 0) {
		int p = -1e5, q = -1e5;
		
		for (int i = 1; i <= n; i++) 
			if (a[i] > p) q = p, p = a[i];
			else if (a[i] > q) q = a[i];
		
		cout << p + q << '\n';
		return 0;	
	} 
	
	for (int i = 1; i <= n; i++) 
		f[i][0] = max(f[i - 1][0] + a[i], a[i]), f[i][1] = min(f[i - 1][1] + a[i], a[i]);
	for (int i = n; i >= 1; i--) 
		g[i][0] = max(g[i + 1][0] + a[i], a[i]), g[i][1] = min(g[i + 1][1] + a[i], a[i]);

	maxx[0][0] = maxx[n + 1][1] = -2e9, minn[0][0] = minn[n + 1][1] = 2e9;
	for (int i = 1; i <= n; i++) 
		maxx[i][0] = max(f[i][0], maxx[i - 1][0]), minn[i][0] = min(f[i][1], minn[i - 1][0]);
	for (int i = n; i >= 1; i--)
		maxx[i][1] = max(g[i][0], maxx[i + 1][1]), minn[i][1] = min(g[i][1], minn[i + 1][1]);
	
	mx = -2e9, mi = 2e9;
	for (int i = 1; i <= n; i++) {
		// cerr << maxx[i][0] << ' ' << maxx[i][1] << '\n';
		mx = max(maxx[i][0] + maxx[i][1] - (maxx[i][0] + maxx[i][1] - a[i] == sum) * a[i], mx);
		mi = min(minn[i][0] + minn[i][1] - (minn[i][0] + minn[i][1] - a[i] == sum) * a[i], mi);
	}

	// cerr << mx << ' ' << mi << ' ' << sum << '\n';
	cout << max(mx, sum - mi) << '\n';
	return 0;
}