#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 50;
int n, m;
int cnt, phi[N], prime[N];
bool isNotPrime[N];
ll ans;

void getPhi(int num) {
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * phi[prime[j]];
		}
	}
	return;
}

void solve() {
	getPhi(max(n, m));
	for (int i = 1; i <= max(n, m); i++) ans += (ll) 2 * (n / i) * (m / i) * phi[i];
	ans -= (ll) n * m;
	cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	solve();
	return 0;
}