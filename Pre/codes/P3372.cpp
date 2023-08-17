#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

const int M = 1e5;
int q;
struct SegTree {
	ll a[M + 50], tr[4 * M + 50];
	int n;
	ll add[4 * M + 50];

	void init(int l, int r, int u) {
		if (l == r) {
			tr[u] = a[l];
			return;
		}
		int lu = 2 * u, ru = 2 * u + 1;		//lu为左儿子，ru为右儿子
		int mid = (l + r) / 2;
		init(l, mid, lu), init(mid + 1, r, ru);
		tr[u] = tr[lu] + tr[ru];
		return;
	}

	ll query(int l, int r, int s, int t, int u) {
		if (l <= s && t <= r) return tr[u];
		int lu = 2 * u, ru = 2 * u + 1;
		int mid = (s + t) / 2;
		ll sum = 0;
		if (add[u]) {
			tr[lu] += add[u] * (mid - s + 1), tr[ru] += add[u] * (t - mid);
			add[lu] += add[u], add[ru] += add[u];
		}
		add[u] = 0;
		if (l <= mid) sum += query(l, r, s, mid, lu);
		if (r > mid) sum += query(l, r, mid + 1, t, ru);
		return sum;
	}

	void update(int l, int r, int s, int t, int u, ll num) {
		if (l <= s && t <= r) {
			tr[u] += (t - s + 1) * num, add[u] += num;
			return;
		}
		int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
		if (add[u] && s != t) {
			tr[lu] += add[u] * (mid - s + 1), tr[ru] += add[u] * (t - mid);
			add[lu] += add[u], add[ru] += add[u];
		}
		add[u] = 0;
		if (l <= mid) update(l, r, s, mid, lu, num);
		if (r > mid) update(l, r, mid + 1, t, ru, num);
		tr[u] = tr[lu] + tr[ru];
		return;
	}
};

SegTree tree;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> tree.n >> q;
	for (int i = 1; i <= tree.n; i++) cin >> tree.a[i];
	tree.init(1, tree.n, 1);
	// cerr << "ok" << endl;
	while (q--) {
		// cout << q << endl;
		int x;
		cin >> x;
		if (x == 1) {
			int a, b;
			ll c;
			cin >> a >> b >> c;
			tree.update(a, b, 1, tree.n, 1, c);
		} else {
			int a, b;
			cin >> a >> b;
			cout << tree.query(a, b, 1, tree.n, 1) << endl;
		}
	}
	return 0;
}