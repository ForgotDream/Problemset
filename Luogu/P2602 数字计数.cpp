#include <iostream>
#include <cstdio>
#include <valarray>

using namespace std;
using ll = long long;

const int N = 15;
ll a, b;
ll ten[N + 1], dp[N + 1];
valarray<ll> av(0ll, 10), bv(0ll, 10);
int num[N + 1];

void init() {
	ten[0] = 1;
	for (int i = 1; i <= N; i++) dp[i] = i * ten[i - 1], ten[i] = 10 * ten[i - 1];
	// for (int i = 1; i <= N; i++) cout << dp[i] << ' ' << ten[i] << endl;
	return;
}

void calc(ll u, valarray<ll> &v) {
	int len = 0;
	while (u) num[++len] = u % 10, u /= 10;
	// cout << len << endl;
	for (int i = len; i >= 1; i--) {
		for (int j = 0; j < 10; j++) v[j] += dp[i - 1] * num[i];
		for (int j = 0; j < num[i]; j++) v[j] += ten[i - 1];
		ll num2 = 0;
		for (int j = i - 1; j >= 1; j--) num2 = num2 * 10 + num[j];
		v[num[i]] += num2 + 1;
		v[0] -= ten[i - 1];
	}
	return;
}

void solve() {
	calc(a - 1, av), calc(b, bv);
	bv -= av;
	for (auto i : bv) cout << i << ' ';
	cout << endl;
	return;
}

int main() {
	cin >> a >> b;
	init();
	solve();
	return 0;
}