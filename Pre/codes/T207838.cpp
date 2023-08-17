#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n;
int a[500];
int f[500][500], sum[500];

void solve() {
	// memset(f, 0x3c, sizeof(f));
	for (int l = 1; l <= n; l++) {
		for (int i = 1, j = i + l; i <= n && j <= n; i++, j = i + l) {
			f[i][j] = 0x3f3f3f3f;
			for (int k = i; k < j; k++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1]);
			}
		}
	}
	cout << f[1][n] << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];
	solve();
	return 0;
}