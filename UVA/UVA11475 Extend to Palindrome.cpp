/**
 * @file    UVA11475 Extend to Palindrome.cpp
 * @author  ForgotDream
 * @brief   Manacher
 * @date    2023-02-19
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 2e5 + 50;
char raw[N], s[2 * N];
int d[2 * N], primeCnt, ans;

void init() {
	int len = strlen(raw + 1);
	memset(d, 0, sizeof(d));
	primeCnt = 0;
	s[0] = '$';
	for (int i = 1; i <= len; i++) {
		s[++primeCnt] = '#', s[++primeCnt] = raw[i];
	}
	s[++primeCnt] = '#', s[++primeCnt] = '|';
	return;
}

int Manacher() {
	int r = 0, mid = 0, res = 0;
	for (int i = 1; i <= primeCnt; i++) {
		d[i] = (i < r) ? min(d[(mid << 1) - i], d[mid] + mid - i) : 1;
		while (s[i + d[i]] == s[i - d[i]]) d[i]++;
		res = max(res, d[i]);
		if (d[i] + i > r) r = d[i] + i, mid = i;
	}
	return res - 1;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	while (cin >> (raw + 1)) {
		init();
		Manacher();
		ans = 0;
		for (int i = 1; i <= primeCnt; i++) {
			if (d[i] + i == primeCnt) {
				ans = max(ans, d[i] - 1);
			}
		}
		cout << raw + 1;
		for (int i = strlen(raw + 1) - ans; i >= 1; i--) {
			cout << raw[i];
		}
		cout << '\n';
	}

	return 0;
}