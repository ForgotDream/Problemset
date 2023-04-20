/**
 * @file    T314206 最大选区和.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-02-12
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 100050;
int n;
i64 a[N], maxx = -1e9;
i64 sum, ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], maxx = max(a[i], maxx);

	ans = a[1];
	for (int i = 1; i <= n; i++) {
		sum = max(sum + a[i], 0ll);
		ans = max(ans, sum);
	}

	if (maxx < 0) cout << maxx << '\n';
	else cout << ans << '\n';

	return 0;
}