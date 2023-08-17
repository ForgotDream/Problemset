#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long ll;

const int M = 2e5;
int n, m;
double sin_[4 * M + 50], cos_[4 * M + 50];
ll lzy[4 * M + 50], a[M + 50];

void pushup(int u) {
	int lu = 2 * u, ru = 2 * u + 1;
	sin_[u] = sin_[lu] + sin_[ru];
	cos_[u] = cos_[lu] + cos_[ru];
	return;
}

void pushdown(int u, int s, int t) {
	int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
	if (lzy[u]) {
		double sin1 = sin(lzy[u]), cos1 = cos(lzy[u]);
		double tmp1 = sin_[lu], tmp2 = sin_[ru];
		sin_[lu] = sin_[lu] * cos1 + cos_[lu] * sin1;
		cos_[lu] = cos_[lu] * cos1 - tmp1 * sin1;
		sin_[ru] = sin_[ru] * cos1 + cos_[ru] * sin1;
		cos_[ru] = cos_[ru] * cos1 - tmp2 * sin1;
		lzy[lu] += lzy[u], lzy[ru] += lzy[u];
		lzy[u] = 0;
	}
	return;
}

void init(int l, int r, int u) {
	if (l == r) {
		sin_[u] = sin(a[l]), cos_[u] = cos(a[l]);
		return;
	}
	int mid = (l + r) / 2, lu = 2 * u, ru = 2 * u + 1;
	init(l, mid , lu), init(mid + 1, r, ru);
	pushup(u);
	return;
}

void update(int l, int r, int s, int t, int u, int num) {
	if (l <= s && t <= r) {
		double sin1 = sin(num), cos1 = cos(num), tmp = sin_[u];
		sin_[u] = sin_[u] * cos1 + cos_[u] * sin1;
		cos_[u] = cos_[u] * cos1 - tmp * sin1;
		lzy[u] += num;
		return;
	}
	pushdown(u, s, t);
	int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
	if (l <= mid) update(l, r, s, mid, lu, num);
	if (r > mid) update(l, r, mid + 1, t, ru, num);
	pushup(u);
	return;
}

double query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return sin_[u];
	pushdown(u, s, t);
	double sum = 0;
	int mid = (s + t) / 2, lu = 2 * u, ru = 2 * u + 1;
	if (l <= mid) sum += query(l, r, s, mid, lu);
	if (r > mid) sum += query(l, r, mid + 1, t, ru);
	return sum;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	init(1, n, 1);
	cin >> m;
	while (m--) {
		int x;
		cin >> x;
		if (x == 1) {
			int a, b, c;
			cin >> a >> b >> c;
			update(a, b, 1, n, 1, c);
		} else {
			int a, b;
			cin >> a >> b;
			cout << fixed << setprecision(1) << query(a, b, 1, n, 1) << endl;
		}
	}
	return 0;
}