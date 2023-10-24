#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 5e4 + 50, INF = 0x3f3f3f3f;
int n, a, b, d;
bool isNotPrime[N];
int mu[N], cnt, prime[N];
ll sum[N], ans;

void getMu(int n) {
	mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && (ll) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) {
				mu[i * prime[j]] = 0;
				break;
			}
			else mu[i * prime[j]] = -1 * mu[i];
		}
	}
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + mu[i];
	return;
}

void solve() {
	a /= d, b /= d, ans = 0;
	for (int l = 1, r; l <= min(a, b); l = r + 1) {
		r = min(a / (a / l), b / (b / l));
		ans += (ll) (sum[r] - sum[l - 1]) * (a / l) * (b / l);
	}
	cout << ans << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	getMu((int)5e4 + 10);
	cin >> n;
	while (n--) cin >> a >> b >> d, solve();
	return 0;
}