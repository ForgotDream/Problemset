#include <bits/stdc++.h>

using namespace std;

static const int K = 1e3 + 50, N = 1e5 + 50;
struct Point {
	int x, y;
	bool operator< (const Point &oth) const {
		if (x == oth.x) {
			return y > oth.y;
		} else {
			return x < oth.x;
		}
	}
} point[K];
map<pair<int, int>, int> mp;
int n, m, k;
int f[K], len = 1;
vector<int> c[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> k;
	for (int i = 1; i <= k; i++) {
		cin >> point[i].x >> point[i].y;
	}

	sort(point + 1, point + k + 1);

	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= k; i++) {
		int pos = lower_bound(f + 1, f + k + 1, point[i].y) - f;
		f[pos] = point[i].y;
		len = max(len, pos);
	}

	cout << (int) round(100 * (n + m) + (sqrt(2) - 2) * 100 * len) << '\n';

	return 0;
}