#include <iostream>
#include <cstdio>

using namespace std;

int n;
int a[1000];
int ans = -1;
int f[1000][1000];

void solve() {
	/*
	for (int len = 2; len <= n; len++) {
		for (int l = 1, r = l + len; l <= 2 * n && r <= 2 * n; l++, r = l + len) {
			for (int k = l; k < r; k++) {
				f[l][r] = max(f[l][r], f[l][k] + f[k + 1][r] + a[l] * a[k + 1] * a[r + 1]);
			}
		}
	}
	*/
	for (int r = 1; r <= 2 * n; r++) {
		for (int l = r - 1; r - l < n && l >= 1; l--) {
			for (int k = l; k < r; k++) {
				f[l][r] = max(f[l][r], f[l][k] + f[k + 1][r] + a[l] * a[k + 1] * a[r + 1]);	
			}
		}
	}
	for (int i = 1; i <= n; i++) ans = max(ans, f[i][i + n - 1]);
	cout << ans << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], a[i + n] = a[i];
	solve();
	return 0;
}