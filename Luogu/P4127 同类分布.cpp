/**
 * @file    P4127 同类分布.cpp
 * @author  ForgotDream
 * @brief   数位 DP
 * @date    2023-02-14
 */
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50, MAX = 9 * 18 + 50, M = 20;
i64 a, b;
i64 f[M][MAX][MAX];
int nums[M], len, mod;

i64 dfs(int cur, int sum, int rst, bool isLimited) {
	i64 res = 0;
	if (sum + 9 * cur < mod) return 0;
	if (!cur) return !rst && sum == mod;
	if (!isLimited && ~f[cur][sum][rst]) return f[cur][sum][rst];

	int up = isLimited ? nums[cur] : 9;
	for (int i = 0; i <= up && i + sum <= mod; i++) {
		res += dfs(cur - 1, sum + i, (rst * 10 + i) % mod, isLimited && i == up);
	}

	if (!isLimited) f[cur][sum][rst] = res;
	return res;
}

i64 calc(i64 num) {
	i64 res = 0;

	len = 0;
	while (num) nums[++len] = num % 10, num /= 10;

	for (int i = 1; i <= 9 * len; i++) {
		memset(f, -1, sizeof(f)), mod = i;
		res += dfs(len, 0, 0, true);
	}

	return res;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> a >> b;
	cout << calc(b) - calc(a - 1) << '\n';

	return 0;
}