/**
 * @file    P3612 Secret Cow Code S.cpp
 * @author  ForgotDream
 * @brief   分治
 * @date    2023-02-14
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 70;
i64 n, len[N], cnt;
string s;

inline i64 calc(i64 idx, int cur) {
	if (idx == 0) return len[cur - 1];
	else return idx;
}

char solve(i64 idx, int cur) {
	if (cur == 1) return s[idx - 1];
	// cerr << idx << ' ' << cur << '\n';
	if (idx > len[cur - 1]) return solve(calc(idx - len[cur - 1] - 1, cur), cur - 1);
	else return solve(idx, cur - 1);
}

inline void init() {
	len[1] = s.length();
	for (cnt = 2; len[cnt - 1] < n; cnt++) 
		len[cnt] = len[cnt - 1] << 1ll;
	return;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> s >> n;
	init();
	cout << solve(n, lower_bound(len + 1, len + cnt, n) - len) << '\n';

	return 0;
}