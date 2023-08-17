#include <iostream>

using namespace std;
using i64 = long long;

const int N = 2e4 + 50;
int n;
i64 a[N], ans, sum, maxx;
int pivot;

int main() {
	freopen("feather.in", "r", stdin);
	freopen("feather.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	
	for (int i = 1; i < n; i++) {
		if (maxx < a[i] + a[i + 1]) {
			// l = pivot;
			maxx = a[i] + a[i + 1];
		}
	}
	
	// if ((n & 1) == 0) {
		cout << max(maxx, a[1] + a[n]) << '\n';
		return 0;
	// }
	
	/*
	int flg = 0;
	ans = a[1];
	int avail = 0, cnt = 0;
	for (int i = 2; i <= n; i++) {
		avail += a[i - 2];
		avail -= a[i];
		flg += a[i - 1] - a[i];
		if (avail < 0) {
			++cnt;
			ans += -1 * avail;
			// flg += -1 * avail;
			avail = 0;
		}
	}
	
	cout << flg << '\n';
	cout << ans + flg << '\n';
	*/
	
	return 0;
}
