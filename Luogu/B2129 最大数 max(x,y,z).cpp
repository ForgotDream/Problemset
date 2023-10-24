/**
 * @file    B2129 最大数 max(x,y,z).cpp
 * @author  ForgotDream
 * @brief   模拟
 * @date    2023-02-23
 */
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;
using i64 = long long;

static const int N = 1e3 + 50, INF = 0x3f3f3f3f;
double a, b, c, ans;

template<typename T>
T max(T a, T b, T c) {
	return max(max(a, b), c);
}

signed main() {
	ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

	cin >> a >> b >> c;

	ans = max(a, b, c) / (max(a + b, b, c) * max(a, b, b + c));

	cout << fixed << setprecision(3) << ans << '\n';

	return 0;
}