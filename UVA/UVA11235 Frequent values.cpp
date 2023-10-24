#include <iostream>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::max;

const int N = 1e5 + 50;
int n, q;
int tmp, lst, cur, cnt, st;
int num[N], left[N], right[N];
int count[N], value[N], a[N];
int lstl;
int l, r;
int rmq[N][25];

void init() {
	/*
	fill(num + 1, num + n + 1, 0);
	fill(left + 1, left + n + 1, 0);
	fill(right + 1, right + n + 1, 0);
	fill(a + 1, a + n + 1, 0);
	fill(count + 1, count + cnt + 1, 0);
	fill(value + 1, value + cnt + 1, 0);
	*/
	cnt = 0, tmp = 0, lst = 0x3f3f3f3f, cur = 0;
	return;
}

void pre() {
	lst = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++) {
		if (a[i] != lst) cnt++, lstl = i, lst = a[i];
		left[i] = lstl, num[i] = cnt;
		value[cnt] = a[i];
	}
	lst = 0x3f3f3f3f;
	for (int i = n; i >= 1; i--) {
		if (a[i] != lst) lstl = i, lst = a[i];
		right[i] = lstl;
	}
	for (int i = 1; i <= n; i = right[i] + 1) {
		count[num[i]] = right[i] - left[i] + 1;
	}
	for (int i = 1; i <= cnt; i++) rmq[i][0] = count[i];
	for (int j = 1; (1 << j) <= cnt; j++)
		for (int i = 1; i + (1 << j) - 1 <= cnt; i++)
			rmq[i][j] = max(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
	return;
}

int RMQ(int s, int t) {
	int k = 0;
	while ((1 << (k + 1)) <= t - s + 1) k++;
	// cout << s << ' ' << t << ' ' << k << endl;
	return max(rmq[s][k], rmq[t - (1 << k) + 1][k]);
}

void solve() {
	cin >> l >> r;
	int ans = -0x3f3f3f3f;
	if (num[l] == num[r]) ans = r - l + 1;
	else if (num[r] - num[l] == 1) ans = max(right[l] - l + 1, r - left[r] + 1);
	else ans = max(max(right[l] - l + 1, r - left[r] + 1), RMQ(num[l] + 1, num[r] - 1));
		// cout << right[l] - l + 1 << ' ' << r - left[r] + 1 << ' ' << RMQ(num[l] + 1, num[r] - 1) << endl;
	cout << ans << endl;
	return;
}

int main() {
	while (cin >> n && n != 0) {
		cin >> q;
		init();
		for (int i = 1; i <= n; i++) cin >> a[i];
		pre();
		while (q--) solve();
	}
	return 0;
}