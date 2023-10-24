#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;

const int M = 1e5;
int n, m, num;
ll a[M + 50];
ll tr[4 * M + 50], maxx[4 * M + 50];

inline ll read() {
	register ll x = 0, t = 1;
	register char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			t = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * t;
}

inline void write(ll x)
{
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

void pushup(int u) {
	tr[u] = tr[2 * u] + tr[2 * u + 1];
	maxx[u] = max(maxx[2 * u], maxx[2 * u + 1]);
	return;
}

void build(int l, int r, int u) {
	if (l == r) {
		tr[u] = a[l];
		maxx[u] = a[l];
		return;
	}
	int mid = (l + r) / 2, lu = 2 * u, ru = 2 * u + 1;
	build(l, mid, lu), build(mid + 1, r, ru);
	pushup(u);
	return;
}

void update(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r && s == t) {
		tr[u] = sqrt(tr[u]);
		maxx[u] = tr[u];
		return;
	}
	int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
	if (l <= mid && maxx[lu] > 1) update(l, r, s, mid, lu);
	if (r > mid && maxx[ru] > 1) update(l, r, mid + 1, t, ru);
	pushup(u);
	return;
}

ll query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tr[u];
	ll sum = 0;
	int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
	if (l <= mid) sum += query(l, r, s, mid, lu);
	if (r > mid) sum += query(l, r, mid + 1, t, ru);
	return sum;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		++num;
		// cout << num << endl;
		for (int i = 1; i <= n; i++) a[i] = read();
		build(1, n, 1);
		m = read();
		printf("Case #%d: \n", num);
		while (m--) {
			int x, l, r;
			x = read(), l = read(), r = read();
			if (l > r) swap(l, r);
			if (x) write(query(min(l, r), max(l, r), 1, n, 1)), putchar('\n');
			else update(min(l, r), max(l, r), 1, n, 1);
		}
		putchar('\n');
	}
	return 0;
}