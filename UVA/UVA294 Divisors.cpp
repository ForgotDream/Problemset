#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e6 + 50;
int T;
ll l, r;
int cnt, prime[N];
bool isNotPrime[N];

void getPrime(int n) {
	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && (ll) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
}

int getDivisorNum(ll num) {
	int res = 1;
	for (int i = 1; (ll) prime[i] * prime[i] <= num && i <= cnt; i++) {
		if (!(num % prime[i])) {
			int tmp = 1;
			while (!(num % prime[i])) num /= prime[i], tmp++;
			res *= tmp;
		}
	}
	if (num > 1) res *= 2;
	return res;
}

void solve() {
	int tmp, ans = 0;
	ll pivot;
	for (ll i = l; i <= r; i++) {
		tmp = getDivisorNum(i);
		// cout << i << ' ' << tmp << endl;
		if (tmp > ans) ans = tmp, pivot = i;
	}
	cout << "Between " << l << " and " << r << ", " << pivot << " has a maximum of " << ans << " divisors." << endl;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	getPrime((int)1e5 + 50);
	cin >> T;
	while (T--) 
		cin >> l >> r, solve();
	return 0;
}