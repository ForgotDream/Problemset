/**
 * @file    P1163 银行贷款.cpp
 * @author  ForgotDream
 * @brief   二分答案
 * @date    2023-02-12
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 100050;
static const double EPS = 1e-6;
int n, m, t;

bool check(double mid) {
	return pow(1.0 / (1.0 + mid), t) > 1 - (double) n /m * mid;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> t;

	double l = 0, r = 5;
	while (l + EPS < r) {
		double mid = (l + r) / 2;
		// cerr << l << ' ' << r << ' ' << mid << ' ' << check(mid) << '\n';
		if (check(mid)) r = mid;
		else l = mid;
	}

	cout << fixed << setprecision(1) << 100 * l << '\n';

	return 0;
}