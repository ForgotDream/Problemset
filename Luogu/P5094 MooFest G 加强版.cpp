/**
 * @file    P5094 MooFest G 加强版.cpp
 * @author  ForgotDream
 * @brief   BIT
 * @date    2023-02-14
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 5e4 + 50, MOD = 1e5 + 3;
struct Node {
	int v, x;
	bool operator<(const Node &oth) const {
		return v < oth.v;
	}
} node[N];
int n, maxx;
i64 tree[N][2], ans;

inline int lowbit(int x) {
	return x & -x;
}

void add(int x, int d, int cur) {
	for (int i = x; i <= maxx; i += lowbit(i))
		tree[i][cur] += d;
	return;
}

i64 sum(int x, int cur) {
	i64 res = 0;
	for (int i = x; i; i -= lowbit(i))
		res += tree[i][cur];
	return res;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) 
		cin >> node[i].v >> node[i].x, maxx = max(maxx, node[i].x);

	sort(node + 1, node + n + 1);
	for (int i = 1; i <= n; i++) {
		add(node[i].x, 1, 0), add(node[i].x, node[i].x, 1);
		ans += (
				  (sum(node[i].x - 1, 0) - (i - sum(node[i].x, 0))) * node[i].x 
				+ sum(maxx, 1) - sum(node[i].x, 1) - sum(node[i].x - 1, 1)
			   ) * node[i].v;
	}

	cout << ans << '\n';
	return 0;
}