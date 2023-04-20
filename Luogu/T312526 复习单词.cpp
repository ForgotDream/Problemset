/**
 * @file    T312526 复习单词.cpp
 * @author  ForgotDream
 * @brief   模拟
 * @date    2023-02-04
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e7 + 50, M = 25;
i64 a[N], n, ans;
int y[2], m[2], dd[2], hour[2], minute[2];
int md[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeap(int year) {
	if (!year) return true;
	if (year % 400 == 0) return true;
	if (year % 4 == 0) {
		if (year % 100 == 0) return false;
		return true;
	}
	return false;
}

i64 getMinute(int d) {
	i64 res = 0;
	for (int i = 0; i < y[d]; i++) 
		res += (i64) (365 + isLeap(i)) * 1440;
	for (int i = 1; i < m[d]; i++) 
		res += (i64) md[i] * 1440;
	if (isLeap(y[d]) && m[d] > 2) res += 1440;
	res += (dd[d] - 1) * 1440;
	res += (hour[d]) * 60;
	res += minute[d];
	return res;
}

int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];

	scanf("%d-%d-%d-%d:%d", &y[0], &m[0], &dd[0], &hour[0], &minute[0]);
	scanf("%d-%d-%d-%d:%d", &y[1], &m[1], &dd[1], &hour[1], &minute[1]);

	// cerr << getMinute(0) << ' ' << getMinute(1) << '\n';
	int d = getMinute(1) - getMinute(0);
	
	sort(a + 1, a + n + 1);

	int cnt = 1;
	while (d >= 0 && cnt <= n) {
		d -= a[cnt], cnt++;
		if (d >= 0) ans++;
	}

	cout << ans << '\n';
	return 0;
}