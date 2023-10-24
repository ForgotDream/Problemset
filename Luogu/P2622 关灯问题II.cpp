#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, int>;

const int N = 15, M = 105, INF = 0x3f3f3f3f;
int n, m, f[1 << N], convert[M][N];

void solve() {
	memset(f, 0x3f, sizeof f), f[(1 << n) - 1] = 0;
	for (int i = (1 << n) - 1; ~i; i--)
		for (int j = 1; j <= m; j++) {
			int cur = i;
			for (int k = 0; k < n; k++) {
				if (convert[j][k] == -1) cur |= (1 << k);
				if (convert[j][k] == 1) cur &= ~(1 << k);
			}
			f[cur] = min(f[cur], f[i] + 1);
		}
	// for (int i = 0; i < (1 << n); i++) cerr << f[i] << endl;
	cout << (f[0] == INF ? -1 : f[0]) << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		for (int j = 0; j < n; j++) cin >> convert[i][j];
	solve();
	return 0;
}