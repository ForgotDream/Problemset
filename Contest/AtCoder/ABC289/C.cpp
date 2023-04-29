#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

static const int N = 15;
int n, m;
int s[N];
i64 ans;

void solve() {
	for (int i = 0; i < (1 << m); i++) {
		int cur = 0, sta = i;
		for (int j = 0; j < m; j++)
			if ((1 << j) & sta) cur |= s[j + 1];
		if (cur == (1 << n) - 1) ans++; 
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	for (int i = 1, c; i <= m; i++) {
		cin >> c;
		for (int j = 1, x; j <= c; j++) 
			cin >> x, s[i] += (1 << (x - 1));
	}

	solve();

	cout << ans << '\n';

	return 0;
}