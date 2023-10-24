/**
 * @file    P1966 火柴排队.cpp
 * @author  ForgotDream
 * @brief   树状数组 + 逆序对
 * @date    2023-02-14
 */
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50, MOD = 1e8 - 3;
int n, pos[N], tree[N], ans;
struct Node {
	int num, no;
	bool operator<(const Node &oth) const {
		return num < oth.num;
	}
} a[N], b[N];

inline int lowbit(int x) {
	return x & -x;
}

int sum(int x) {
	int res = 0;
	for (int i = x; i; i -= lowbit(i)) 
		(res += tree[i]) %= MOD;
	return res;
}

void add(int x, int d) {
	for (int i = x; i <= n; i += lowbit(i)) 
		tree[i] += d;
	return;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].num, a[i].no = i;
	for (int i = 1; i <= n; i++) cin >> b[i].num, b[i].no = i;

	sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) pos[b[i].no] = a[i].no;

	for (int i = 1; i <= n; i++) {
		add(pos[i], 1);
		(ans += i - sum(pos[i])) %= MOD;
	}

	cout << ans << '\n';
	return 0;
}