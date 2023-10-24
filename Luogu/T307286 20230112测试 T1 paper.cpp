#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll n, m, ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	while (n && m) {
		if (n < m) swap(n, m);
		ll tmp = n / m;
		n -= m * tmp, ans += tmp;
	}
	cout << ans << endl;
	return 0;
}