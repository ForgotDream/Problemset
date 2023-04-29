#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 15, M = 1e5 + 50;
int n, m, x;
int a[N];
bool f[M], b[M];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cin >> m;
	for (int i = 1, u; i <= m; i++) cin >> u, b[u] = true;
	cin >> x;

	f[0] = true;
	for (int i = 1; i <= x; i++) {
		if (b[i]) continue;
		for (int j = 1; j <= n; j++) if (i >= a[j]) f[i] |= f[i - a[j]];
	}

	if (f[x]) cout << "Yes" << '\n';
	else cout << "No" << '\n';

	return 0;
}