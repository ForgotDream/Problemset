#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 1e5;
int tr[4 * N + 50], a[N + 50];
int n, m;

void pushup(int u) {
	int lu = 2 * u, ru = 2 * u + 1;
	tr[u] = min(tr[lu], tr[ru]);
	return;
}

void build(int l, int r, int u) {
	if (l == r) {
		tr[u] = a[l];
		return;
	}
	int mid = (l + r) / 2;
	int lu = 2 * u, ru = 2 * u + 1;
	build(l, mid, lu), build(mid + 1, r, ru);
	pushup(u);
	return;
}

int query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tr[u];
	int mid = (s + t) / 2;
	int lu = 2 * u, ru = 2 * u + 1;
	int sum = 0x7fffffff;
	if (l <= mid) sum = min(sum, query(l, r, s, mid, lu));
	if (r > mid) sum = min(sum, query(l, r, mid + 1, t, ru));
	return sum;
}

int main() {
	cin >> n >> m;
	memset(tr, 0x3f, sizeof(tr));
	for (int i = 1; i <= n; i++) cin >> a[i];
	build(1, n, 1);
	while (m--) {
		int a, b;
		cin >> a >> b;
		cout << query(a, b, 1, n, 1) << " ";
	}
	return 0;
}