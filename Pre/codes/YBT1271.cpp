#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int m, n;
int k;
int o2[1050], n2[1050], w[1050];
double f[1050][1050];

void solve() {
	memset(f, 127, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= k; i++)
		for (int j = m; j >= 0; j--)
			for (int l = n; l >= 0; l--) {
				int a = min(m, j + o2[i]), b = min(n, l + n2[i]);
				f[a][b] = min(f[j][l] + w[i], f[a][b]);
			}
	cout << f[m][n] << endl;
	return;
}

int main() {
	cin >> m >> n;
	cin >> k;
	for (int i = 1; i <= k; i++)
		cin >> o2[i] >> n2[i] >> w[i];
	solve();
	return 0;
}