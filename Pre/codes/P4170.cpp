#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n, cnt;
char str[60];
int f[60][60];

void solve() {
	memset(f, 0x3f, sizeof f);
	for (int i = 0; i < n; i++) f[i][i] = 1;
	for (int len = 2; len <= n; len++)
		for (int l = 0; l + len - 1 < n; l++) {
			int r = l + len - 1;
			if (str[l] == str[r])
				f[l][r] = min(f[l + 1][r], f[l][r - 1]);
			else {
				for (int k = l; k < r; k++) f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
			}
		}
	cout << f[0][n - 1] << endl;
	return;
}

int main() {
	// cin >> n;
	// for (int i = 1; i <= n; i++) cin >> str[i];
	cin >> str;
	n = strlen(str);
	solve();
	return 0;
}