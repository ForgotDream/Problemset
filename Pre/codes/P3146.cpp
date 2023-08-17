#include <iostream>
#include <cstdio>

using namespace std;

int n, ans;
int a[250];
int f[250][250];

void solve() {
	for (int i = 1; i <= n; i++) f[i][i] = a[i];
	for (int r = 2; r <= n; r++)
		for (int l = r - 1; l >= 1 && r - l < n; l--)
			for (int k = l; k < r; k++)
				if (f[l][k] == f[k + 1][r]) 
					f[l][r] = max(f[l][r], f[l][k] + 1), ans = max(ans, f[l][r]);
	cout << ans << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	solve();
	return 0;
}