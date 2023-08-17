#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

const int M = 2e5;
int n, m;
int tr[4 * M + 50], a[M + 50];

void pushup(int u) {
	tr[u] = max(tr[2 * u], tr[2 * u + 1]);
	// cout << " " << tr[u] << endl;
	return;
}

void init(int l, int r, int u) {
	if (l == r) {
		tr[u] = a[l];
		// cout << u << " " << tr[u] << endl;
		return;
	}
	int mid = (l + r) / 2, lu = 2 * u, ru = 2 * u + 1;
	init(l, mid, lu), init(mid + 1, r, ru);
	pushup(u);
	// tr[u] = max(tr[lu], tr[ru]);
	return;
}

void update(int l, int r, int u, int x, int y) {
	if (l == r) {
		tr[u] = max(tr[u], y);
		return;
	}
	int mid = (l + r) / 2, lu = 2 * u, ru = 2 * u + 1;
	if (x <= mid) update(l, mid, lu, x, y);
	else update(mid + 1, r, ru, x, y);
	pushup(u);
	// tr[u] = max(tr[lu], tr[ru]);
	return;
}

int query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tr[u];
	int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
	int sum = -0x3f3f3f3f;
	if (l <= mid) sum = max(query(l, r, s, mid, lu), sum);
	if (r > mid) sum = max(query(l, r, mid + 1, t, ru), sum);
	return sum;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	// for (int i = 1; i <= n; i++) cout << a[i] << " ";
	// cout << endl;
	init(1, n, 1);
	while (m--) {
		char x;
		int a, b;
		cin >> x >> a >> b;
		if (x == 'Q') cout << query(a, b, 1, n, 1) << endl;
		else update(1, n, 1, a, b);
	}
	return 0;
}