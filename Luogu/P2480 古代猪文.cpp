/**
 * @file    P2480 古代猪文.cpp
 * @author  ForgotDream
 * @brief   Euler 定理 + Lucas 定理 + CRT + 快速幂
 * @date    2023-02-05
 */
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i128 = __int128;

static const int N = 1e6 + 5, MOD = 999911659, FACT[] = {0, 2, 3, 4679, 35617};
int n, g;
int fac[N], a[N];

int fastPow(int base, int p, int mod) {
	int res = 1;
	while (p) {
		if (p & 1) res = (i64) res * base % mod;
		base = (i64) base * base % mod;
		p >>= 1;
	}
	return res;
}

int C(int n, int m, int mod) {
	if (m > n) return 0;
	return (i128) fac[n] * fastPow(fac[n - m], mod - 2, mod) * fastPow(fac[m], mod - 2, mod) % mod;
} 

int Lucas(int n, int m, int mod) {
	if (!m) return 1ll;
	return (i128) Lucas(n / mod, m / mod, mod) * C(n % mod, m % mod, mod) % mod;
}

int CRT() {
	int res = 0;
	for (int i = 1; i <= 4; i++) {
		int m = (MOD - 1) / FACT[i], inv = fastPow(m, FACT[i] - 2, FACT[i]);
		// cerr << inv << '\n';
		res = (i128) (res + (i128) a[i] * inv * m) % (MOD - 1);
	}
	// cerr << res << '\n';
	return (res % MOD + MOD) % MOD;
}

void init(int mod) {
	fac[0] = 1;
	for (int i = 1; i <= mod; i++) fac[i] = fac[i - 1] * i % mod;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> g;
	
	if (g == MOD) {
		cout << 0 << '\n';
		return 0;
	}

	for (int j = 1; j <= 4; j++) {
		init(FACT[j]);
		for (int i = 1; i * i <= n; i++) 
			if (!(n % i)) {
				a[j] = (i128) (a[j] + Lucas(n, i, FACT[j])) % FACT[j];
				if (i * i != n) a[j] = (i128) (a[j] + Lucas(n, n / i, FACT[j])) % FACT[j];
 			}
	}

	cout << fastPow(g, CRT(), MOD) % MOD << '\n';
	return 0;
}