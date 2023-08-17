#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll n, m, ans;

void solve() {
	while (n && m) {
		if (n < m) swap(n, m);
		ll tmp = n / m;
		ans += tmp;
		n -= m * tmp;
	}
	cout << ans << endl;
	return;
}

int main() {
	freopen("paper.in", "r", stdin);
	freopen("paper.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	solve();
	return 0;
}