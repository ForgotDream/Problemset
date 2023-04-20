#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int l, n;
int a[55];
int f[55][55];

void solve() {
	a[n + 1] = l;
	for (int len = 2; len <= n + 1; len++) 
		for (int l = 0; l + len <= n + 1; l++) {
			int r = l + len, minn = 0x3f3f3f3f;
			for (int k = l + 1; k < r; k++) minn = min(minn, f[l][k] + f[k][r]);
			f[l][r] = minn + a[r] - a[l];
			// cout << len << ' ' << l << ' ' << r << ' ' << minn << ' ' << f[l][r] << endl;
		}
	cout << "The minimum cutting is " << f[0][n + 1] << "." << endl;
	return;
}

int main() {
	while (cin >> l && l != 0) {
		memset(f, 0, sizeof f);
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i], f[i][i + 1] = 0;
		solve();
	}
	return 0;
}