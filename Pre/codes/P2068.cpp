#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

const int M = 1e5;
int n, w;
char ch;

ll tr[4 * M + 50];

void pushup(int u) {
	tr[u] = tr[2 * u] + tr[2 * u + 1];
	return;
}

void update(int l, int r, int s, int t, int u, int num) {
	if (l <= s && t <= r) {
		tr[u] += num;
		return;
	}
	int mid = (s + t) / 2;
	int lu = 2 * u, ru = 2 * u + 1;
	if (l <= mid) update(l, r, s, mid, lu, num);
	if (r > mid) update(l, r, mid + 1, t, ru, num);
	pushup(u);
	return;
}

ll query(int l, int r, int s, int t, int u) {
	if (l <= s && t <= r) return tr[u];
	int mid = (s + t) / 2;
	int lu = 2 * u, ru = 2 * u + 1;
	ll sum = 0;
	if (l <= mid) sum += query(l, r, s, mid, lu);
	if (r > mid) sum += query(l, r, mid + 1, t, ru);
	return sum;
}

int main() {
	cin >> n >> w;
	while (w--) {
		cin >> ch;
		if (ch == 'x') {
			int a, b;
			cin >> a >> b;
			update(a, a, 1, n, 1, b);
		} else {
			int a, b;
			cin >> a >> b;
			cout << query(a, b, 1, n, 1) << endl;
		}
	}
	return 0;
}