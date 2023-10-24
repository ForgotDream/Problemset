/**
 * @file    P1824 进击的奶牛.cpp
 * @author  ForgotDream
 * @brief   二分答案
 * @date    2023-02-12
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 100050;
int n, c;
int a[N];

bool check(int mid) {
	int pivot = 1, lst = a[1];
	for (int i = 2; i <= n; i++) {
		if (a[i] >= lst + mid) lst = a[i], pivot++;
	}
	return pivot >= c;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> c;
	for (int i = 1; i <= n; i++) cin >> a[i];

	int l = 0, r = 1e9;
	sort(a + 1, a + n + 1);
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		// cerr << l << ' ' << r << ' ' << mid << ' ' << check(mid) << '\n';
		if (check(mid)) l = mid;
		else r = mid - 1;
	}

	cout << r << '\n';
	return 0;
}