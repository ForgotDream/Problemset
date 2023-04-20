/**
 * @file    P3853 路标设置.cpp
 * @author  ForgotDream
 * @brief   二分答案
 * @date    2023-02-12
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 100050;
int l, n, k;
int a[N], gap[N];

bool check(int mid) {
	int tmp = k;
	for (int i = 1; i <= n + 1; i++) {
		if (gap[i] <= mid) continue;
		tmp -= gap[i] / mid + (gap[i] % mid != 0) - 1;
	}
	return tmp >= 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> l >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i], gap[i] = a[i] - a[i - 1];
	gap[n + 1] = l - a[n];

	// for (int i = 1; i <= n + 1; i++) cerr << gap[i] << '\n';
	
	int L = 1, R = 0;
	for (int i = 1; i <= n + 1; i++) R = max(R, gap[i]);
	while (L < R) {
		int mid = (L + R) >> 1;
		// cerr << L << ' ' << R << ' ' << mid << ' ' << check(mid) << '\n';
		if (check(mid)) R = mid;
		else L = mid + 1;
	}

	cout << L << '\n';
	return 0;
}