#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e6 + 50;

int a, b, d;
bool isNotPrime[N];
int mu[N], cnt, prime[N];
ll ans;

inline void getMu(int n) {
	mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && (ll)i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) {
				mu[i * prime[j]] = 0;
				break;
			}
			else mu[i * prime[j]] = -1 * mu[i];
		}
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> a >> b >> d, a /= d, b /= d;
	getMu(min(a, b));
	for (int i = 1; i <= min(a, b); i++) ans += (ll) (a / i) * (b / i) * mu[i];
	cout << ans << endl;
	return 0;
}