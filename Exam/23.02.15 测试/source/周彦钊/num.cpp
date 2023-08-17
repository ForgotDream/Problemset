#include <iostream>

using namespace std;
using i64 = long long;

static const int N = 1e5 + 50;
static const i64 MOD = 1e9 + 7;
int n;
i64 ans, a[N], sum;

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
	freopen("num.in", "r", stdin);
	freopen("num.out", "w", stdout);
	
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	if (n == 1) cin >> a[1] >> a[2], cout << (2 * a[1] % MOD * a[2]) % MOD << '\n';
	else {
		cin >> a[1];
		// (ans = a[1] * a[2]) %= MOD;
		
		/* O(n ^ 2) 写法： 
		for (int i = 3; i <= n + 1; i++) {
			(ans *= 2) %= MOD;
			cin >> a[i];
			for (int j = 3; j <= i - 1; j++) 
				(ans += fastPow(2, j - 2, MOD) * a[i] % MOD * a[j] % MOD) %= MOD;
			(ans += (a[1] + a[2]) % MOD * a[i] % MOD) %= MOD;	
		}
		*/
		
		for (int i = 2; i <= n + 1; i++) {
			cin >> a[i];
			// (ans += fastPow(2, n - i + 1, MOD) % MOD * a[1] % MOD * a[i] % MOD) %= MOD;
			(sum += fastPow(2, n - i + 1, MOD) * a[i] % MOD) %= MOD;
		}
		// cout << sum << '\n';
		for (int i = 1; i <= n; i++) {
			(ans += a[i] * sum % MOD) %= MOD;
			// cout << a[i] << ' ' << sum << '\n';
			// cout << ans << '\n';
			sum = ((sum - fastPow(2, n - i, MOD) * a[i + 1]) % MOD + MOD) % MOD;
			// cout << sum << '\n';
			if (i != 1) (sum *= 2) %= MOD;
		}
	}
	
	cout << (2 * ans) % MOD << '\n';
	return 0;
}
