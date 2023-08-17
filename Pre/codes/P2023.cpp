#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

const int M = 1e5;
int m, p;

struct SegTree {
	int n;
	int a[M + 50];
	ll tr[4 * M + 50], mul[4 * M + 50], add[4 * M + 50];

	void pushup(int i) {
		tr[i] = (tr[2 * i] + tr[2 * i + 1]) % p;
		return;
	}

	void pushdown(int s, int t, int i) {
		int li = i * 2, ri = i * 2 + 1;
		int mid = (s + t) / 2;
		if (mul[i] != 1) {
			mul[li] = (mul[li] * mul[i]) % p, mul[ri] = (mul[ri] * mul[i]) % p;
			add[li] = (add[li] * mul[i]) % p, add[ri] = (add[ri] * mul[i]) % p;
			tr[li] = (tr[li] * mul[i]) % p, tr[ri] = (tr[ri] * mul[i]) % p;
			mul[i] = 1;
		}
		if (add[i]) {
			add[li] = (add[li] + add[i]) % p, add[ri] = (add[ri] + add[i]) % p;
			tr[li] = (tr[li] + (add[i] * (mid - s + 1))) % p, tr[ri] = (tr[ri] + (add[i] * (t - mid))) % p;
			add[i] = 0;
		}
		return;
	}

	void init(int l, int r, int u) {
		mul[u] = 1;
		if (l == r) {
			tr[u] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		int lu = 2 * u, ru = 2 * u + 1;
		init(l, mid, lu), init(mid + 1, r, ru);
		pushup(u);
		return;
	}

	void update1(int l, int r, int s, int t, int u, ll num) {
		if (l <= s && t <= r) {
			mul[u] = (mul[u] * num) % p;
			add[u] = (add[u] * num) % p;
			tr[u] = (tr[u] * num) % p;
			return;
		}
		int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
		pushdown(s, t, u);
		if (l <= mid) update1(l, r, s, mid, lu, num);
		if (r > mid) update1(l, r, mid + 1, t, ru, num);
		pushup(u);
		return;
	}

	void update2(int l, int r, int s, int t, int u, ll num) {
		if (l <= s && t <= r) {
			add[u] = (add[u] + num) % p;
			tr[u] = (tr[u] + (num * (t - s + 1))) % p;
			return;
		}
		int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
		pushdown(s, t, u);
		if (l <= mid) update2(l, r, s, mid, lu, num);
		if (r > mid) update2(l, r, mid + 1, t, ru, num);
		pushup(u);
		return;
	}

	ll query(int l, int r, int s, int t, int u) {
		if (l <= s && t <= r) return tr[u];
		int mid = (s + t) / 2;
		int lu = 2 * u, ru = 2 * u + 1;
		ll ans = 0;
		pushdown(s, t, u);
		if (l <= mid) ans = (ans + query(l, r, s, mid, lu)) % p;
		if (r > mid) ans = (ans + query(l, r, mid + 1, t, ru)) % p;
		return ans;
	}

} tree;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> tree.n >> p;
	for (int i = 1; i <= tree.n; i++) cin >> tree.a[i];
	tree.init(1, tree.n, 1);
	cin >> m;
	while (m--) {
		int x;
		cin >> x;
		if (x == 1) {
			int a, b;
			ll c;
			cin >> a >> b >> c;
			tree.update1(a, b, 1, tree.n, 1, c);
		} else if (x == 2) {
			int a, b;
			ll c;
			cin >> a >> b >> c;
			tree.update2(a, b, 1, tree.n, 1, c);
		} else {
			int a, b;
			cin >> a >> b;
			cout << tree.query(a, b, 1, tree.n, 1) << endl;
		}
	}
	return 0;
}