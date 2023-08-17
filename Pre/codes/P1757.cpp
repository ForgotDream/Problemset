#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

int m, n, ans = -1;
int a[1050], b[1050], c[1050];
int num[1050];
int f[1050];
int g[1050][1050];
int cnt = 1;

void solve() {
	for (int i = 1; i <= cnt; i++)
		for (int j = m; j >= 0; j--)
			for (int k = 1; k <= num[i]; k++)
				if (j >= a[g[i][k]])
					f[j] = max(f[j], f[j - a[g[i][k]]] + b[g[i][k]]);
	cout << f[m] << endl;
	return;
}

int main() {
	cin >> m >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i];
		cnt = max(cnt, c[i]);
		num[c[i]]++;
		g[c[i]][num[c[i]]] = i;
	}
	solve();
	return 0;
}