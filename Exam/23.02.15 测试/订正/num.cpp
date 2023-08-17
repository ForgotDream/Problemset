#include <iostream>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50;
static const i64 MOD = 1e9 + 7;
int n;
i64 ans, a[N], sum, sum2;

i64 fastPow(i64 base, i64 p, i64 mod) {
	i64 res = 1;
	while (p) {
		if (p & 1) (res *= base) %= mod;
		(base *= base) %= mod;
		p >>= 1;
	}
	return res;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	cin >> a[1];
	for (int i = 2; i <= n + 1; i++) {
		cin >> a[i];
		(sum += fastPow(2, n - i + 2, MOD) * a[i] % MOD) %= MOD;
	}
	
	for (int i = 1; i <= n; i++) {
		(ans += a[i] * sum % MOD) %= MOD;
		cerr << sum << '\n';
		sum = ((sum - fastPow(2, n - i + 1, MOD) * a[i + 1]) % MOD + MOD) % MOD;
		if (i != 1) (sum *= 2) %= MOD;
	}
	
	cout << (ans) % MOD << '\n';
	return 0;
}
