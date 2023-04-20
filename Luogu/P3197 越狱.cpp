/**
 * @file    P3197 越狱.cpp
 * @author  ForgotDream
 * @brief   数学 + 计数
 * @date    2023-02-14
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50, MOD = 1e5 + 3;
i64 m, n;

i64 fastPow(i64 base, i64 p, i64 mod) {
	i64 res = 1;
	while (p) {
		if (p & 1) (res *= base) %= mod;
		(base *= base) %= mod;
		p >>= 1;
	}
	return res;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> m >> n;
	cout << ((fastPow(m, n, MOD) - m * fastPow(m - 1, n - 1, MOD)) % MOD + MOD) % MOD << '\n';

	return 0;
}