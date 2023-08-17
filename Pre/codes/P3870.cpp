#include <iostream>
#include <cstdio>

using namespace std;

const int M = 2e6;
int n, m;
int tr[5 * M + 50], a[M + 50];
char ch;
bool lzy[5 * M + 50];

void pushup(int u) {
	tr[u] = tr[2 * u] + tr[2 * u + 1];
	return;
}

void pushdown(int s, int t, int u) {
	int lu = 2 * u, ru = 2 * u + 1, mid = (s + t) / 2, len = t - s + 1;
	if (lzy[u]) {
		lzy[lu] ^= 1, lzy[ru] ^= 1;
		tr[lu] = len - len / 2 - tr[lu], tr[ru] = len / 2 - tr[ru];
		lzy[u] = false;
	}
	return;
}

void update(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) {
		lzy[u] ^= 1, tr[u] = t - s + 1 - tr[u];
		return;
	}
	pushdown(s, t, u);
	int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
	if (l <= mid) update(l, r, s, mid, lu);
	if (r > mid) update(l, r, mid + 1, t, ru);
	pushup(u);
	return;
}

int query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tr[u];
	pushdown(s, t, u);
	int sum = 0;
	int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
	if (l <= mid) sum += query(l, r, s, mid, lu);
	if (r > mid) sum += query(l, r, mid + 1, t, ru);
	return sum;
}

int main() {
	cin >> n >> m;
	while (m--) {
		int x, a, b;
		cin >> x;
		if (x) {
			cin >> a >> b;
			cout << query(a, b, 1, n, 1) << endl;
		} else {
			cin >> a >> b;
			update(a, b, 1, n, 1);
		}
	}
	return 0;
}