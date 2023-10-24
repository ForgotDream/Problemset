#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 1e4 + 50, M = 5.5e3 + 100, K = 505, INF = 0x3f3f3f3f;
int n, k, a[N], maxx;
int f[N][K], tree[K][M];

inline int lowbit(int x) {
	return x & -x;
}

inline void update(int x, int y, int num) {
	for (int i = x; i <= k + 1; i += lowbit(i))
		for (int j = y; j <= maxx + k; j += lowbit(j))
			tree[i][j] = max(tree[i][j], num);
	return;
}

inline int query(int x, int y) {
	int res = 0;
	for (int i = x; i; i -= lowbit(i)) 
		for (int j = y; j; j -= lowbit(j))
			res = max(res, tree[i][j]);
	return res;
}

void solve() {
	for (int i = 1; i <= n; i++) 
		for (int j = k; ~j; j--)
			f[i][j] = query(j + 1, a[i] + j) + 1, update(j + 1, a[i] + j, f[i][j]);
	cout << query(k + 1, maxx + k) << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i], maxx = max(maxx, a[i]);
	solve();
	return 0;
}