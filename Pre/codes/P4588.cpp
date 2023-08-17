#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

int t, q;
ll m;
ll tr[4 * (int)1e5 + 50];

void pushup(int u) {
	tr[u] = ((tr[2 * u] % m) * (tr[2 * u + 1] % m)) % m;
	return;
}

void init(int l, int r, int u) {
	if (l == r) {
		tr[u] = 1;
		return;
	}
	int mid = (l + r) / 2, lu = 2 * u, ru = 2 * u + 1;
	init(l, mid, lu), init(mid + 1, r, ru);
	pushup(u);
	// tr[u] = 1;
	return;
}

void update(int l, int r, int s, int t, int u, int num) {
	if (l <= s && t <= r) {
		tr[u] = num;
		return;
	}
	int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
	if (l <= mid) update(l, r, s, mid, lu, num);
	if (r > mid) update(l, r, mid + 1, t, ru, num);
	pushup(u);
	return;
}

void solve() {
	cin >> q >> m;
	init(1, q, 1);
	for (int i = 1; i <= q; i++) {
		int x, num;
		cin >> x >> num;
		if (x == 1)
			update(i, i, 1, q, 1, num);
		else
			update(num, num, 1, q, 1, 1);
		cout << (tr[1] % m) << endl;
	}
	return;
}

int main() {
	cin >> t;
	while (t--) solve();
	return 0;
}