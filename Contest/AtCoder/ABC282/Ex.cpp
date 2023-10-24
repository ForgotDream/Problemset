#include <iostream>
#include <cstdio>

using namespace std;
using ll = long long;

const int N = 2e5 + 50;
const ll INF = 1e18;
ll a[N], b[N], s, ssum[N], tree[N << 2];
int n, ans;

void pushup(int u) {
	return (void)(tree[u] = min(tree[u << 1], tree[u << 1 | 1]));
}

void build(int l, int r, int u) {
	if (l == r) return (void)(tree[u] = a[l]);
	int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
	build(l, mid, lc), build(mid + 1, r, rc);
	pushup(u);
	return;
}

ll query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tree[u];
	int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
	ll res = INF;
	if (l <= mid) res = min(res, query(l, r, s, mid, lc));
	if (r > mid) res = min(res, query(l, r, mid + 1, t, rc));
	return res;
}

ll sum(int l, int r) {
	return ssum[r] - ssum[l - 1];
}

void solve() {
	build(1, n, 1);
	int l = 1, r = 1;
	while (r <= n) {
		while (sum(l, r) + query(l, r, 1, n, 1) <= s && r <= n) ans++, r++, cerr << l << ' ' << r << endl;
		while (sum(l, r) + query(l, r, 1, n, 1) > s && l <= r) l++;
	}
	cout << ans << endl;
	return;
}

int main() {
	cin >> n >> s;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i], ssum[i] = b[i] + ssum[i - 1];
	solve();
	return 0;
}