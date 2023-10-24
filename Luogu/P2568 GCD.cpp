#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e7 + 50;
int n;
int phi[N], cnt, prime[N];
bool isNotPrime[N];
ll ans, sum[N];

void getPhi(int n) {
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && (ll) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * phi[prime[j]];
		}
	}
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + phi[i];
	return;
}

void solve() {
	getPhi(n);
	for (int i = 1; i <= cnt; i++) ans += 2 * sum[n / prime[i]] - 1;
	cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	solve();
	return 0;
}