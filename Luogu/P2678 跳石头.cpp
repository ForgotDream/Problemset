/**
 * @file    P2678 跳石头.cpp
 * @author  ForgotDream
 * @brief   二分答案
 * @date    2023-02-12
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 100050;
int l, n, m;
int a[N];

bool check(int mid) {
	int cnt = 0, lst = 0;
	for (int i = 1; i <= n + 1; i++) {
		if (a[i] - lst < mid) cnt++;
		else lst = a[i];
	}
	return cnt <= m;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> l >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];

	a[n + 1] = l;
	int L = 1, R = l + 1;
	while (L + 1 < R) {
		int mid = (L + R) >> 1;
		if (check(mid)) L = mid;
		else R = mid;
	}
	
	cout << L << '\n';
	return 0;
}