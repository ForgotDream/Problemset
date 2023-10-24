/**
 * @file    T314207 不定区间最大和.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-02-12
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 1e7 + 50;
int n;
i64 f[N][2], a[N], maxx, sum;
i64 mx = -0x7fffffffffffffff, mi = 0x7fffffffffffffff;
bool flg = false;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i], maxx = max(maxx, a[i]);
		sum += a[i];
		if (a[i] >= 0) flg = true;
	}

	for (int i = 1; i <= n; i++) {
		f[i][0] = max(f[i - 1][0] + a[i], a[i]);
		f[i][1] = min(f[i - 1][1] + a[i], a[i]);
	}

	for (int i = 1; i <= n; i++) mx = max(mx, f[i][0]), mi = min(mi, f[i][1]);

	if (!flg) cout << maxx << '\n';
	else cout << max(sum - mi, mx) << '\n';

	return 0;
}