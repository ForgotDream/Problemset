/**
 * @file    CF1207F Remainder Problem.cpp
 * @author  ForgotDream
 * @brief   根号分治
 * @date    2023-02-05
 */
#include <bits/stdc++.h>


using namespace std;
using i64 = long long;
// using i128 = __int128;

static const int N = 5e5 + 50, M = 705;
int q;
i64 s[M][M], a[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> q;

	while (q--) {
		int opt, x, y;
		cin >> opt >> x >> y;
		if (opt == 1) {
			for (int i = 1; i <= 700; i++) s[i][x % i] += y;
			a[x] += y;
		} else {
			if (x <= 700) cout << s[x][y] << '\n';
			else {
				i64 res = 0;
				for (int i = y; i <= 5e5; i += x) res += a[i];
				cout << res << '\n';
			}
 		}
	}
	return 0;
}