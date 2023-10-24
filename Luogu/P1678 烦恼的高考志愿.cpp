/**
 * @file    P1678 烦恼的高考志愿.cpp
 * @author  ForgotDream
 * @brief   二分搜索
 * @date    2023-02-12
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 100050;
int n, m;
int a[N], b[N];
i64 ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> m >> n;
	for (int i = 1; i <= m; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];

	sort(a + 1, a + m + 1);

	for (int i = 1; i <= n; i++) {
		int l = lower_bound(a + 1, a + m + 1, b[i]) - a, r = l - 1;
		if (l == 1) ans += abs(a[l] - b[i]);
		else if (l == m + 1) ans += abs(a[r] - b[i]);
		else ans += min(abs(a[l] - b[i]), abs(a[r] - b[i]));
	}

	cout << ans << '\n';
	return 0;
}