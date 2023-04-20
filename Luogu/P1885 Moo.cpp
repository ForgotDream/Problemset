/**
 * @file    P1885 Moo.cpp
 * @author  ForgotDream
 * @brief   分治
 * @date    2023-02-13
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50, MOD = 10000;
int n;
i64 len[30], l[30], r[30];

char solve(int idx, int cur) {
	if (!cur) return idx == 1 ? 'm' : 'o';
	if (l[cur] <= idx && idx <= r[cur]) {
		if (idx == l[cur]) return 'm';
		else return 'o';
	} 
	else if (idx > r[cur]) 
		return solve(idx - r[cur], cur - 1);
	else return solve(idx, cur - 1);
}

void init() {
	// len[27] >= 1e9
	len[0] = 3;
	for (int i = 1; i <= 27; i++) {
		len[i] = 2 * len[i - 1] + i + 3;
		l[i] = len[i - 1] + 1, r[i] = l[i] + i + 2;
	}
	return;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	init();
	cin >> n;
	cout << solve(n, lower_bound(len + 1, len + 28, n) - len) << '\n';

	return 0;
}