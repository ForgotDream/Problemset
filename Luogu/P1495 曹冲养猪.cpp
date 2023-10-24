#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

const int M = 15;
int n;
ll a[M], b[M];

ll exgcd(ll a, ll b, ll& x, ll& y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, x, y);
	ll t = x;
	x = y, y = t - a / b * y;
	return d;
}

void solve() {
	ll m = 1, res = 0;
	for (int i = 1; i <= n; i++) m *= b[i];
	for (int i = 1; i <= n; i++) {
		ll k = m / b[i], x, y;
		exgcd(k, b[i], x, y);
		res = (res + a[i] * k * x % m) % m;
	}
	cout << (res % m + m) % m << endl;
	return;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> b[i] >> a[i];
	}
	solve();
	return 0;
}